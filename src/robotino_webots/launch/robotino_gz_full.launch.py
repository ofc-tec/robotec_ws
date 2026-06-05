#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    robotino_webots_share = get_package_share_directory("robotino_webots")
    # robotino_audio_share = get_package_share_directory("robotino_audio")
    rto_description_share = get_package_share_directory("rto_description")

    nav_launch = os.path.join(robotino_webots_share, "launch", "nav_robotino_gz.launch.py")
    # speech_launch = os.path.join(robotino_audio_share, "launch", "speech_recog.launch.py")

    map_file = LaunchConfiguration("map_file")
    use_sim_time = LaunchConfiguration("use_sim_time")
    gui = LaunchConfiguration("gui")
    rviz = LaunchConfiguration("rviz")
    robotino_gz_launch = LaunchConfiguration("robotino_gz_launch")
    robot_description_topic = LaunchConfiguration("robot_description_topic")
    rviz_node_name = LaunchConfiguration("rviz_node_name")
    publish_initial_map_to_odom = LaunchConfiguration("publish_initial_map_to_odom")
    image_topic = LaunchConfiguration("image_topic")
    depth_topic = LaunchConfiguration("depth_topic")
    depth_info_topic = LaunchConfiguration("depth_info_topic")
    yolo_confidence_threshold = LaunchConfiguration("yolo_confidence_threshold")
    yolo_input_color = LaunchConfiguration("yolo_input_color")
    robotino_spawn_x = LaunchConfiguration("robotino_spawn_x")
    robotino_spawn_y = LaunchConfiguration("robotino_spawn_y")
    robotino_spawn_z = LaunchConfiguration("robotino_spawn_z")
    robotino_spawn_yaw = LaunchConfiguration("robotino_spawn_yaw")

    include_nav = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(nav_launch),
        launch_arguments={
            "map_file": map_file,
            "use_sim_time": use_sim_time,
            "gui": gui,
            "rviz": rviz,
            "robotino_gz_launch": robotino_gz_launch,
            "robot_description_topic": robot_description_topic,
            "rviz_node_name": rviz_node_name,
            "publish_initial_map_to_odom": publish_initial_map_to_odom,
            "robotino_spawn_x": robotino_spawn_x,
            "robotino_spawn_y": robotino_spawn_y,
            "robotino_spawn_z": robotino_spawn_z,
            "robotino_spawn_yaw": robotino_spawn_yaw,
        }.items(),
    )

    vision_node = Node(
        package="vision",
        executable="vision_node",
        name="vision_node",
        output="screen",
        parameters=[{
            "image_topic": image_topic,
        }],
    )

    yolo_server = Node(
        package="vision",
        executable="yolo_server",
        name="yolo_server",
        output="screen",
        parameters=[{
            "image_topic": image_topic,
            "depth_topic": depth_topic,
            "depth_info_topic": depth_info_topic,
            "confidence_threshold": yolo_confidence_threshold,
            "yolo_input_color": yolo_input_color,
            "log_image_stats": True,
        }],
    )

    face_recog_server = Node(
        package="vision",
        executable="face_recog_service_node",
        name="face_recog_service_node",
        output="screen",
        parameters=[{
            "image_topic": image_topic,
            "depth_topic": depth_topic,
            "depth_info_topic": depth_info_topic,
        }],
    )

    pose_service_node = Node(
        package="vision",
        executable="pose_service_node",
        name="pose_service_node",
        output="screen",
        parameters=[{
            "image_topic": image_topic,
            "depth_topic": depth_topic,
            "depth_info_topic": depth_info_topic,
        }],
    )

    # Audio is intentionally left out for YOLO/CUDA test launches.
    # include_speech = IncludeLaunchDescription(PythonLaunchDescriptionSource(speech_launch))

    kinect_depth_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="kinect_depth_tf_glue",
        arguments=["0", "0", "0", "0", "0", "0", "kinect_link", "kinect_depth"],
        output="screen",
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            "map_file",
            default_value=os.path.expanduser("~/robotino_ros2_ws/map_2.yaml"),
            description="Path to map YAML file",
        ),
        DeclareLaunchArgument(
            "use_sim_time",
            default_value="true",
            description="Use Gazebo simulation time",
        ),
        DeclareLaunchArgument(
            "gui",
            default_value="true",
            description="Start Gazebo GUI",
        ),
        DeclareLaunchArgument(
            "rviz",
            default_value="true",
            description="Start RViz with Nav2 view",
        ),
        DeclareLaunchArgument(
            "robotino_gz_launch",
            default_value=os.path.join(rto_description_share, "launch", "robotino_gz_wheels.launch.py"),
            description="Optional Robotino Gazebo base launch file passed through to nav_robotino_gz",
        ),
        DeclareLaunchArgument(
            "robot_description_topic",
            default_value="/robot_description",
            description="Topic where Robotino republishes robot_description",
        ),
        DeclareLaunchArgument(
            "rviz_node_name",
            default_value="rviz2",
            description="Node name for the Nav2 RViz process",
        ),
        DeclareLaunchArgument(
            "publish_initial_map_to_odom",
            default_value="true",
            description="Publish bootstrap map -> odom until AMCL owns localization",
        ),
        DeclareLaunchArgument(
            "image_topic",
            default_value="/kinect_sim/rgb/image_raw",
            description="RGB image topic for vision nodes",
        ),
        DeclareLaunchArgument(
            "depth_topic",
            default_value="/kinect_sim/depth/image_raw",
            description="Depth image topic for vision nodes",
        ),
        DeclareLaunchArgument(
            "depth_info_topic",
            default_value="/kinect_sim/depth/camera_info",
            description="Depth camera info topic for 3D vision nodes",
        ),
        DeclareLaunchArgument(
            "yolo_confidence_threshold",
            default_value="0.25",
            description="YOLO confidence threshold passed to the vision server",
        ),
        DeclareLaunchArgument(
            "yolo_input_color",
            default_value="bgr",
            description="Color order passed to the YOLO server: bgr or rgb",
        ),
        DeclareLaunchArgument("robotino_spawn_x", default_value="0.0"),
        DeclareLaunchArgument("robotino_spawn_y", default_value="0.0"),
        DeclareLaunchArgument("robotino_spawn_z", default_value="0.0"),
        DeclareLaunchArgument("robotino_spawn_yaw", default_value="0.0"),
        include_nav,
        vision_node,
        yolo_server,
        # face_recog_server,
        # pose_service_node,
        kinect_depth_tf,
        # include_speech,
    ])
