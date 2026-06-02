#!/usr/bin/env python3

import os
import re
from pathlib import Path

import yaml
from ament_index_python.packages import get_package_prefix, get_package_share_directory
from launch import LaunchDescription
from launch.actions import (
    DeclareLaunchArgument,
    IncludeLaunchDescription,
    OpaqueFunction,
    RegisterEventHandler,
    SetEnvironmentVariable,
    TimerAction,
)
from launch.event_handlers import OnProcessExit
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch.conditions import IfCondition
from launch_ros.substitutions import FindPackageShare
from uf_ros_lib.moveit_configs_builder import MoveItConfigsBuilder
from uf_ros_lib.uf_robot_utils import get_xacro_content, generate_ros2_control_params_temp_file


def add_virtual_mount_link(robot_description, link_name):
    if f'<link name="{link_name}"' in robot_description:
        return robot_description
    robot_tag = robot_description.find("<robot")
    insert_at = robot_description.find(">", robot_tag) + 1
    return (
        robot_description[:insert_at]
        + f'\n  <link name="{link_name}" />\n'
        + robot_description[insert_at:]
    )


def add_gz_ros_namespace(robot_description, namespace):
    if not namespace:
        return robot_description
    plugin_tag = '<plugin filename="gz_ros2_control-system" name="gz_ros2_control::GazeboSimROS2ControlPlugin">'
    if plugin_tag not in robot_description:
        return robot_description
    plugin_start = robot_description.find(plugin_tag)
    plugin_end = robot_description.find("</plugin>", plugin_start)
    plugin_xml = robot_description[plugin_start:plugin_end]
    if "<namespace>" in plugin_xml:
        return robot_description
    return robot_description.replace(
        plugin_tag,
        f"{plugin_tag}\n        <ros>\n          <namespace>{namespace}</namespace>\n        </ros>",
        1,
    )


def remove_gz_sensors_system_plugin(robot_description):
    return re.sub(
        r"\n?\s*<gazebo>\s*"
        r"<plugin\s+filename=\"lib?gz-sim-sensors-system(?:\.so)?\"\s+name=\"gz::sim::systems::Sensors\">\s*"
        r"<render_engine>.*?</render_engine>\s*"
        r"</plugin>\s*"
        r"</gazebo>\s*",
        "\n",
        robot_description,
        count=1,
        flags=re.DOTALL,
    )


def namespace_moveit_controllers(moveit_config_dict, namespace):
    if not namespace:
        return
    simple_manager = moveit_config_dict.get("moveit_simple_controller_manager", {})
    controller_names = simple_manager.get("controller_names", [])
    renamed = []
    for name in controller_names:
        if name.startswith("/") or name.startswith(f"{namespace}/"):
            renamed.append(name)
            continue
        namespaced_name = f"{namespace}/{name}"
        if name in simple_manager and namespaced_name not in simple_manager:
            simple_manager[namespaced_name] = simple_manager.pop(name)
        renamed.append(namespaced_name)
    simple_manager["controller_names"] = renamed


def add_virtual_joint_to_srdf(robot_description_semantic, joint_name, parent_frame, child_link):
    if f'name="{joint_name}"' in robot_description_semantic:
        return robot_description_semantic
    robot_tag = robot_description_semantic.find("<robot")
    insert_at = robot_description_semantic.find(">", robot_tag) + 1
    virtual_joint = (
        f'\n  <virtual_joint name="{joint_name}" type="floating" '
        f'parent_frame="{parent_frame}" child_link="{child_link}" />\n'
    )
    return robot_description_semantic[:insert_at] + virtual_joint + robot_description_semantic[insert_at:]


def launch_setup(context, *args, **kwargs):
    robotino_webots_share = get_package_share_directory("robotino_webots")
    xarm_gazebo_prefix = get_package_prefix("xarm_gazebo")
    rto_description_share = get_package_share_directory("rto_description")
    xarm_description_share = get_package_share_directory("xarm_description")
    xarm_controller_share = get_package_share_directory("xarm_controller")

    map_file = LaunchConfiguration("map_file")
    use_sim_time = LaunchConfiguration("use_sim_time")
    gui = LaunchConfiguration("gui")
    rviz = LaunchConfiguration("rviz")
    xarm_rviz = LaunchConfiguration("xarm_rviz")
    run_action_servers = LaunchConfiguration("run_action_servers")
    robotino_gz_launch = LaunchConfiguration("robotino_gz_launch")
    gz_world_name = LaunchConfiguration("gz_world_name")
    xarm_spawn_x = LaunchConfiguration("xarm_spawn_x")
    xarm_spawn_y = LaunchConfiguration("xarm_spawn_y")
    xarm_spawn_z = LaunchConfiguration("xarm_spawn_z")
    xarm_spawn_roll = LaunchConfiguration("xarm_spawn_roll")
    xarm_spawn_pitch = LaunchConfiguration("xarm_spawn_pitch")
    xarm_spawn_yaw = LaunchConfiguration("xarm_spawn_yaw")

    dof = LaunchConfiguration("dof", default="6")
    robot_type = LaunchConfiguration("robot_type", default="xarm")
    prefix = LaunchConfiguration("prefix", default="")
    hw_ns = LaunchConfiguration("hw_ns", default="xarm")
    limited = LaunchConfiguration("limited", default="true")
    effort_control = LaunchConfiguration("effort_control", default="false")
    velocity_control = LaunchConfiguration("velocity_control", default="false")
    add_gripper = LaunchConfiguration("add_gripper", default="false")
    add_vacuum_gripper = LaunchConfiguration("add_vacuum_gripper", default="false")
    add_bio_gripper = LaunchConfiguration("add_bio_gripper", default="false")
    add_realsense_d435i = LaunchConfiguration("add_realsense_d435i", default="true")
    spawn_realsense_gazebo = LaunchConfiguration("spawn_realsense_gazebo", default="false")
    add_d435i_links = LaunchConfiguration("add_d435i_links", default="true")
    model1300 = LaunchConfiguration("model1300", default="false")
    robot_sn = LaunchConfiguration("robot_sn", default="")

    ros2_control_plugin = "gz_ros2_control/GazeboSimSystem"
    ros_namespace = LaunchConfiguration("xarm_ros_namespace", default="").perform(context)
    controller_manager = f"/{ros_namespace}/controller_manager" if ros_namespace else "/controller_manager"
    xarm_robot_description_topic = (
        f"/{ros_namespace}/robot_description" if ros_namespace else "/robot_description"
    )
    xarm_type = f"{robot_type.perform(context)}{dof.perform(context)}"

    ros2_control_params = generate_ros2_control_params_temp_file(
        os.path.join(xarm_controller_share, "config", f"{xarm_type}_controllers.yaml"),
        prefix=prefix.perform(context),
        add_gripper=add_gripper.perform(context) in ("True", "true"),
        add_bio_gripper=add_bio_gripper.perform(context) in ("True", "true"),
        ros_namespace=ros_namespace,
        update_rate=1000,
        use_sim_time=True,
        robot_type=robot_type.perform(context),
    )

    moveit_config = (
        MoveItConfigsBuilder(
            context=context,
            dof=dof,
            robot_type=robot_type,
            prefix=prefix,
            hw_ns=hw_ns,
            limited=limited,
            effort_control=effort_control,
            velocity_control=velocity_control,
            model1300=model1300,
            robot_sn=robot_sn,
            attach_to=LaunchConfiguration("xarm_attach_to"),
            attach_xyz=LaunchConfiguration("xarm_attach_xyz"),
            attach_rpy=LaunchConfiguration("xarm_attach_rpy"),
            ros2_control_plugin=ros2_control_plugin,
            ros2_control_params=ros2_control_params,
            add_gripper=add_gripper,
            add_vacuum_gripper=add_vacuum_gripper,
            add_bio_gripper=add_bio_gripper,
            add_realsense_d435i=add_realsense_d435i,
            add_d435i_links=add_d435i_links,
        )
        .sensors_3d()
        .to_moveit_configs()
    )
    moveit_config_dict = moveit_config.to_dict()
    mount_link = LaunchConfiguration("xarm_attach_to").perform(context)
    moveit_config_dict["robot_description"] = add_virtual_mount_link(
        moveit_config_dict["robot_description"],
        mount_link,
    )
    moveit_config_dict["robot_description_semantic"] = add_virtual_joint_to_srdf(
        moveit_config_dict["robot_description_semantic"],
        "robotino_xarm_world_joint",
        "world",
        mount_link,
    )
    namespace_moveit_controllers(moveit_config_dict, ros_namespace)
    moveit_config_dump = yaml.dump(moveit_config_dict)

    ros_robot_description = {
        "robot_description": add_virtual_mount_link(
            get_xacro_content(
                context,
                xacro_file=Path(xarm_description_share) / "urdf" / "xarm_device.urdf.xacro",
                dof=dof,
                robot_type=robot_type,
                prefix=prefix,
                hw_ns=hw_ns,
                limited=limited,
                effort_control=effort_control,
                velocity_control=velocity_control,
                model1300=model1300,
                robot_sn=robot_sn,
                attach_to=LaunchConfiguration("xarm_attach_to"),
                attach_xyz=LaunchConfiguration("xarm_attach_xyz"),
                attach_rpy=LaunchConfiguration("xarm_attach_rpy"),
                ros2_control_plugin=ros2_control_plugin,
                ros2_control_params=ros2_control_params,
                add_gripper=add_gripper,
                add_vacuum_gripper=add_vacuum_gripper,
                add_bio_gripper=add_bio_gripper,
                add_realsense_d435i=add_realsense_d435i,
                add_d435i_links=add_d435i_links,
            ),
            mount_link,
        )
    }

    gazebo_xacro_content = get_xacro_content(
        context,
        xacro_file=Path(xarm_description_share) / "urdf" / "xarm_device.urdf.xacro",
        dof=dof,
        robot_type=robot_type,
        prefix=prefix,
        hw_ns=hw_ns,
        limited=limited,
        effort_control=effort_control,
        velocity_control=velocity_control,
        model1300=model1300,
        robot_sn=robot_sn,
        attach_to="gazebo_xarm_mount_link",
        attach_xyz="0 0 0",
        attach_rpy="0 0 0",
        ros2_control_plugin=ros2_control_plugin,
        ros2_control_params=ros2_control_params,
        add_gripper=add_gripper,
        add_vacuum_gripper=add_vacuum_gripper,
        add_bio_gripper=add_bio_gripper,
        add_realsense_d435i=spawn_realsense_gazebo,
        add_d435i_links=add_d435i_links,
    )
    gazebo_robot_description = {
        "robot_description": remove_gz_sensors_system_plugin(
            add_gz_ros_namespace(
                add_virtual_mount_link(
                    gazebo_xacro_content,
                    "gazebo_xarm_mount_link",
                ),
                ros_namespace,
            )
        )
    }

    robotino_full = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            os.path.join(robotino_webots_share, "launch", "robotino_gz_full.launch.py")
        ),
        launch_arguments={
            "map_file": map_file,
            "use_sim_time": use_sim_time,
            "gui": gui,
            "rviz": rviz,
            "robotino_gz_launch": robotino_gz_launch,
            "robot_description_topic": "/robotino/robot_description",
            "rviz_node_name": "robotino_nav_rviz",
            "publish_initial_map_to_odom": "false",
            "image_topic": "/camera/color/image_raw",
            "depth_topic": "/camera/depth/image",
            "depth_info_topic": "/camera/depth/camera_info",
        }.items(),
    )

    xarm_state_publisher = Node(
        package="robot_state_publisher",
        executable="robot_state_publisher",
        name="xarm_robot_state_publisher",
        namespace="",
        output="screen",
        parameters=[
            {"use_sim_time": use_sim_time},
            ros_robot_description,
        ],
        remappings=[
            ("/robot_description", xarm_robot_description_topic),
            ("joint_states", f"/{ros_namespace}/joint_states" if ros_namespace else "/joint_states"),
        ],
    )

    spawn_xarm = Node(
        package="ros_gz_sim",
        executable="create",
        name="spawn_robotino_xarm",
        output="screen",
        arguments=[
            "-world",
            gz_world_name,
            "-param",
            "robot_description",
            "-name",
            "UF_ROBOT",
            "-x",
            xarm_spawn_x,
            "-y",
            xarm_spawn_y,
            "-z",
            xarm_spawn_z,
            "-R",
            xarm_spawn_roll,
            "-P",
            xarm_spawn_pitch,
            "-Y",
            xarm_spawn_yaw,
        ],
        parameters=[{"use_sim_time": use_sim_time}, gazebo_robot_description],
    )

    xarm_camera_bridge = Node(
        condition=IfCondition(spawn_realsense_gazebo),
        package="ros_gz_bridge",
        executable="parameter_bridge",
        name="xarm_camera_bridge",
        output="screen",
        arguments=[
            "/camera/color/image_raw@sensor_msgs/msg/Image@gz.msgs.Image",
            "/camera/color/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo",
            "/camera/infra1/image_raw@sensor_msgs/msg/Image@gz.msgs.Image",
            "/camera/infra1/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo",
            "/camera/infra2/image_raw@sensor_msgs/msg/Image@gz.msgs.Image",
            "/camera/infra2/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo",
            "/camera/depth/points@sensor_msgs/msg/PointCloud2@gz.msgs.PointCloudPacked",
            "/camera/depth/camera_info@sensor_msgs/msg/CameraInfo@gz.msgs.CameraInfo",
            "/camera/depth/depth_image@sensor_msgs/msg/Image@gz.msgs.Image",
        ],
        remappings=[
            ("/camera/depth/depth_image", "/camera/depth/image"),
        ],
    )

    xarm_pointcloud_sanitizer = Node(
        condition=IfCondition(spawn_realsense_gazebo),
        package="pc_tools",
        executable="pc_repub_sanitized_cpp",
        name="pc_repub_sanitized_cpp",
        output="screen",
        parameters=[
            {
                "leaf_size": 0.03,
                "keep_every": 2,
                "use_sim_time": use_sim_time,
            }
        ],
    )

    xarm_moveit = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([
                FindPackageShare("robotino_webots"),
                "launch",
                "robotino_xarm_moveit_common.launch.py",
            ])
        ),
        launch_arguments={
            "prefix": prefix,
            "attach_to": LaunchConfiguration("xarm_attach_to"),
            "attach_xyz": LaunchConfiguration("xarm_attach_xyz"),
            "attach_rpy": LaunchConfiguration("xarm_attach_rpy"),
            "show_rviz": xarm_rviz,
            "use_sim_time": use_sim_time,
            "moveit_config_dump": moveit_config_dump,
            "rviz_config": os.path.join(robotino_webots_share, "config", "robotino_xarm_moveit.rviz"),
            "octomap_frame": "world",
        }.items(),
    )

    xarm_depth_camera_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="xarm_depth_camera_static_tf",
        output="screen",
        arguments=[
            "0.06746",
            "-0.0175",
            "0.0237",
            "0.7071",
            "0",
            "0.7071",
            "0",
            "link6",
            "UF_ROBOT/link6/cameradepth",
        ],
    )

    map_to_world_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="map_to_world_static_tf",
        output="screen",
        arguments=[
            "0",
            "0",
            "0",
            "0",
            "0",
            "0",
            "1",
            "map",
            "world",
        ],
    )

    controller_spawners = [
        Node(
            package="controller_manager",
            executable="spawner",
            output="screen",
            arguments=["joint_state_broadcaster", "--controller-manager", controller_manager],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
        Node(
            package="controller_manager",
            executable="spawner",
            output="screen",
            arguments=[f"{prefix.perform(context)}{xarm_type}_traj_controller", "--controller-manager", controller_manager],
            parameters=[{"use_sim_time": use_sim_time}],
        ),
    ]
    if robot_type.perform(context) != "lite" and add_gripper.perform(context) in ("True", "true"):
        controller_spawners.append(
            Node(
                package="controller_manager",
                executable="spawner",
                output="screen",
                arguments=[
                    f"{prefix.perform(context)}{robot_type.perform(context)}_gripper_traj_controller",
                    "--controller-manager",
                    controller_manager,
                ],
                parameters=[{"use_sim_time": use_sim_time}],
            )
        )

    move_group_interface_params = {
        "robot_description": moveit_config_dict["robot_description"],
        "robot_description_semantic": moveit_config_dict["robot_description_semantic"],
        "robot_description_kinematics": moveit_config_dict["robot_description_kinematics"],
    }
    action_servers = TimerAction(
        period=12.0,
        actions=[
            Node(
                package="xarm_pose_action",
                executable="set_joints_action_server",
                name="set_joints_action_server",
                output="screen",
                parameters=[
                    move_group_interface_params,
                    {
                        "planning_group": "xarm6",
                        "action_name": "set_joints",
                        "execute": True,
                        "velocity_scaling": 0.9,
                        "acceleration_scaling": 0.9,
                        "planning_time": 25.0,
                        "planning_attempts": 10,
                        "use_sim_time": use_sim_time,
                    },
                ],
            ),
            Node(
                package="xarm_pose_action",
                executable="set_pose_action_server",
                name="set_pose_action_server",
                output="screen",
                parameters=[
                    move_group_interface_params,
                    {
                        "planning_group": "xarm6",
                        "end_effector_link": "link_eef",
                        "action_name": "set_pose",
                        "execute": True,
                        "cartesian": False,
                        "velocity_scaling": 0.3,
                        "acceleration_scaling": 0.1,
                        "position_tolerance": 0.01,
                        "orientation_tolerance": 0.05,
                        "planning_time": 25.0,
                        "planning_attempts": 10,
                        "use_sim_time": use_sim_time,
                    },
                ],
            ),
        ],
    )

    actions = [
        SetEnvironmentVariable(
            "CYCLONEDDS_URI",
            "file://" + os.path.join(robotino_webots_share, "config", "cyclonedds_many_nodes.xml"),
        ),
        SetEnvironmentVariable(
            "GZ_SIM_SYSTEM_PLUGIN_PATH",
            os.pathsep.join([
                os.path.join(xarm_gazebo_prefix, "lib"),
                "/opt/ros/jazzy/lib",
                os.environ.get("GZ_SIM_SYSTEM_PLUGIN_PATH", ""),
            ]),
        ),
        robotino_full,
        TimerAction(
            period=4.0,
            actions=[
                xarm_state_publisher,
                spawn_xarm,
                xarm_camera_bridge,
                xarm_pointcloud_sanitizer,
                xarm_moveit,
                map_to_world_tf,
                xarm_depth_camera_tf,
                RegisterEventHandler(
                    event_handler=OnProcessExit(
                        target_action=spawn_xarm,
                        on_exit=controller_spawners,
                    )
                ),
            ],
        ),
    ]

    if run_action_servers.perform(context) in ("True", "true"):
        actions.append(action_servers)

    return actions


def generate_launch_description():
    return LaunchDescription([
        DeclareLaunchArgument(
            "map_file",
            default_value=os.path.expanduser("~/robotino_ros2_ws/map_2.yaml"),
            description="Path to map YAML file",
        ),
        DeclareLaunchArgument("use_sim_time", default_value="true"),
        DeclareLaunchArgument(
            "gui",
            default_value="false",
            description="Keep the combined Gazebo run server-first by default. Enable only after /clock, /odom, and camera topics are stable.",
        ),
        DeclareLaunchArgument("rviz", default_value="true"),
        DeclareLaunchArgument("xarm_rviz", default_value="true"),
        DeclareLaunchArgument("run_action_servers", default_value="true"),
        DeclareLaunchArgument(
            "robotino_gz_launch",
            default_value=os.path.join(
                get_package_share_directory("rto_description"),
                "launch",
                "robotino_gz_wheels_table_xarm.launch.py",
            ),
            description="Robotino Gazebo launch file used by the combined Robotino+xArm stack",
        ),
        DeclareLaunchArgument(
            "gz_world_name",
            default_value="robotino_gz_wheels",
            description="Gazebo world name used by ros_gz_sim create when spawning xArm",
        ),
        DeclareLaunchArgument("dof", default_value="6"),
        DeclareLaunchArgument("robot_type", default_value="xarm"),
        DeclareLaunchArgument("prefix", default_value=""),
        DeclareLaunchArgument("hw_ns", default_value="xarm"),
        DeclareLaunchArgument("limited", default_value="true"),
        DeclareLaunchArgument("effort_control", default_value="false"),
        DeclareLaunchArgument("velocity_control", default_value="false"),
        DeclareLaunchArgument("add_gripper", default_value="true"),
        DeclareLaunchArgument("add_vacuum_gripper", default_value="false"),
        DeclareLaunchArgument("add_bio_gripper", default_value="false"),
        DeclareLaunchArgument("add_realsense_d435i", default_value="true"),
        DeclareLaunchArgument(
            "spawn_realsense_gazebo",
            default_value="true",
            description="Spawn the xArm Gazebo realsense sensors. The duplicate Sensors system plugin is stripped from the xArm model because Robotino's world owns rendering.",
        ),
        DeclareLaunchArgument("add_d435i_links", default_value="true"),
        DeclareLaunchArgument("model1300", default_value="false"),
        DeclareLaunchArgument("robot_sn", default_value=""),
        DeclareLaunchArgument("xarm_ros_namespace", default_value=""),
        DeclareLaunchArgument("xarm_attach_to", default_value="xarm_mount_link"),
        DeclareLaunchArgument(
            "xarm_attach_xyz",
            default_value='"0.18 0 0.06"',
            description="xArm base pose relative to Robotino's xarm_mount_link in the combined model",
        ),
        DeclareLaunchArgument("xarm_attach_rpy", default_value='"0 0 0"'),
        DeclareLaunchArgument(
            "xarm_spawn_x",
            default_value="0.18",
            description="Gazebo spawn X for the xArm model; should match xarm_attach_xyz in the combined launch",
        ),
        DeclareLaunchArgument("xarm_spawn_y", default_value="0.0"),
        DeclareLaunchArgument(
            "xarm_spawn_z",
            default_value="0.66",
            description="Gazebo spawn Z for the xArm model; raised above the Robotino table top",
        ),
        DeclareLaunchArgument("xarm_spawn_roll", default_value="0"),
        DeclareLaunchArgument("xarm_spawn_pitch", default_value="0"),
        DeclareLaunchArgument("xarm_spawn_yaw", default_value="0"),
        OpaqueFunction(function=launch_setup),
    ])
