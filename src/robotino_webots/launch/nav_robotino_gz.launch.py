#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    robotino_webots_share = get_package_share_directory("robotino_webots")
    rto_description_share = get_package_share_directory("rto_description")
    nav2_bringup_share = get_package_share_directory("nav2_bringup")

    gz_launch = LaunchConfiguration("robotino_gz_launch")
    urdf_path = os.path.join(robotino_webots_share, "urdf", "Robotino3.urdf")
    nav2_params_path = os.path.join(
        robotino_webots_share, "config", "nav2_robotino_gz.yaml"
    )

    with open(urdf_path, "r") as urdf_file:
        robot_description = urdf_file.read()

    map_file = LaunchConfiguration("map_file")
    use_sim_time = LaunchConfiguration("use_sim_time")
    gui = LaunchConfiguration("gui")
    rviz = LaunchConfiguration("rviz")

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
            description="Robotino Gazebo base launch file",
        ),

        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(gz_launch),
            launch_arguments={"gui": gui}.items(),
        ),

        TimerAction(
            period=2.0,
            actions=[
                Node(
                    package="robot_state_publisher",
                    executable="robot_state_publisher",
                    name="robot_state_publisher",
                    output="screen",
                    parameters=[{
                        "robot_description": robot_description,
                        "use_sim_time": use_sim_time,
                        "publish_frequency": 30.0,
                    }],
                )
            ],
        ),

        TimerAction(
            period=3.0,
            actions=[
                Node(
                    package="tf2_ros",
                    executable="static_transform_publisher",
                    name="map_to_odom",
                    arguments=["0", "0", "0", "0", "0", "0", "map", "odom"],
                )
            ],
        ),

        TimerAction(
            period=3.0,
            actions=[
                Node(
                    package="tf2_ros",
                    executable="static_transform_publisher",
                    name="base_link_to_gz_rplidar",
                    arguments=[
                        "0.18", "0", "0.25",
                        "0", "0", "0",
                        "base_link", "robotec/base_link/rplidar",
                    ],
                )
            ],
        ),

        TimerAction(
            period=4.0,
            actions=[
                Node(
                    package="nav2_map_server",
                    executable="map_server",
                    name="map_server",
                    output="screen",
                    parameters=[{
                        "use_sim_time": use_sim_time,
                        "yaml_filename": map_file,
                        "frame_id": "map",
                    }],
                )
            ],
        ),

        TimerAction(
            period=6.0,
            actions=[
                Node(
                    package="nav2_amcl",
                    executable="amcl",
                    name="amcl",
                    output="screen",
                    parameters=[nav2_params_path, {"use_sim_time": use_sim_time}],
                )
            ],
        ),

        TimerAction(
            period=8.0,
            actions=[
                Node(
                    package="nav2_controller",
                    executable="controller_server",
                    name="controller_server",
                    output="screen",
                    parameters=[nav2_params_path, {"use_sim_time": use_sim_time}],
                )
            ],
        ),

        TimerAction(
            period=10.0,
            actions=[
                Node(
                    package="nav2_planner",
                    executable="planner_server",
                    name="planner_server",
                    output="screen",
                    parameters=[
                        nav2_params_path,
                        {
                            "use_sim_time": use_sim_time,
                            "local_costmap.obstacle_layer.observation_persistence": 0.0,
                        },
                    ],
                )
            ],
        ),

        TimerAction(
            period=11.0,
            actions=[
                Node(
                    package="nav2_smoother",
                    executable="smoother_server",
                    name="smoother_server",
                    output="screen",
                    parameters=[nav2_params_path, {"use_sim_time": use_sim_time}],
                )
            ],
        ),

        TimerAction(
            period=12.0,
            actions=[
                Node(
                    package="nav2_behaviors",
                    executable="behavior_server",
                    name="behavior_server",
                    output="screen",
                    parameters=[nav2_params_path, {"use_sim_time": use_sim_time}],
                )
            ],
        ),

        TimerAction(
            period=15.0,
            actions=[
                Node(
                    package="nav2_bt_navigator",
                    executable="bt_navigator",
                    name="bt_navigator",
                    output="screen",
                    parameters=[nav2_params_path, {"use_sim_time": use_sim_time}],
                )
            ],
        ),

        TimerAction(
            period=17.0,
            actions=[
                Node(
                    package="nav2_lifecycle_manager",
                    executable="lifecycle_manager",
                    name="lifecycle_manager_navigation",
                    output="screen",
                    parameters=[{
                        "use_sim_time": use_sim_time,
                        "autostart": True,
                        "node_names": [
                            "map_server",
                            "amcl",
                            "controller_server",
                            "planner_server",
                            "smoother_server",
                            "behavior_server",
                            "bt_navigator",
                        ],
                    }],
                )
            ],
        ),

        TimerAction(
            period=20.0,
            actions=[
                Node(
                    package="rviz2",
                    executable="rviz2",
                    name="rviz2",
                    parameters=[{"use_sim_time": use_sim_time}],
                    arguments=[
                        "-d",
                        os.path.join(nav2_bringup_share, "rviz", "nav2_default_view.rviz"),
                    ],
                    condition=IfCondition(rviz),
                )
            ],
        ),
    ])
