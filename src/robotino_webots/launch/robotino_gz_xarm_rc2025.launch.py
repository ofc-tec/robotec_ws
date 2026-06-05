#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess, IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    robotino_webots_share = get_package_share_directory("robotino_webots")
    rto_description_share = get_package_share_directory("rto_description")
    map_file = LaunchConfiguration("map_file")
    gui = LaunchConfiguration("gui")
    rviz = LaunchConfiguration("rviz")
    xarm_rviz = LaunchConfiguration("xarm_rviz")
    gz_world_name = LaunchConfiguration("gz_world_name")
    yolo_confidence_threshold = LaunchConfiguration("yolo_confidence_threshold")
    robotino_spawn_x = LaunchConfiguration("robotino_spawn_x")
    robotino_spawn_y = LaunchConfiguration("robotino_spawn_y")
    robotino_spawn_z = LaunchConfiguration("robotino_spawn_z")
    robotino_spawn_yaw = LaunchConfiguration("robotino_spawn_yaw")
    initial_pose_x = LaunchConfiguration("initial_pose_x")
    initial_pose_y = LaunchConfiguration("initial_pose_y")
    initial_pose_yaw_z = LaunchConfiguration("initial_pose_yaw_z")
    initial_pose_yaw_w = LaunchConfiguration("initial_pose_yaw_w")

    return LaunchDescription([
        DeclareLaunchArgument(
            "map_file",
            default_value=os.path.expanduser("~/robotino_ros2_ws/map_slam_rc2025.yaml"),
            description="Path to map YAML file used by Nav2/map_server.",
        ),
        DeclareLaunchArgument(
            "gui",
            default_value="true",
            description="Start Gazebo GUI. Set false for server-only Gazebo.",
        ),
        DeclareLaunchArgument(
            "rviz",
            default_value="true",
            description="Start Robotino Nav2 RViz.",
        ),
        DeclareLaunchArgument(
            "xarm_rviz",
            default_value="true",
            description="Start xArm MoveIt RViz.",
        ),
        DeclareLaunchArgument(
            "gz_world_name",
            default_value="robotino_rc2025_xarm",
            description="Gazebo world name used by xArm and object spawns.",
        ),
        DeclareLaunchArgument(
            "yolo_confidence_threshold",
            default_value="0.25",
            description="YOLO confidence threshold for table object detections.",
        ),
        DeclareLaunchArgument("robotino_spawn_x", default_value="2.443"),
        DeclareLaunchArgument("robotino_spawn_y", default_value="-0.528"),
        DeclareLaunchArgument("robotino_spawn_z", default_value="0.0"),
        DeclareLaunchArgument("robotino_spawn_yaw", default_value="-3.068"),
        DeclareLaunchArgument("initial_pose_x", default_value="2.443"),
        DeclareLaunchArgument("initial_pose_y", default_value="-0.528"),
        DeclareLaunchArgument("initial_pose_yaw_z", default_value="-0.999"),
        DeclareLaunchArgument("initial_pose_yaw_w", default_value="0.037"),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(robotino_webots_share, "launch", "robotino_gz_xarm.launch.py")
            ),
            launch_arguments={
                "gui": gui,
                "rviz": rviz,
                "xarm_rviz": xarm_rviz,
                "map_file": map_file,
                "gz_world_name": gz_world_name,
                "yolo_confidence_threshold": yolo_confidence_threshold,
                "robotino_spawn_x": robotino_spawn_x,
                "robotino_spawn_y": robotino_spawn_y,
                "robotino_spawn_z": robotino_spawn_z,
                "robotino_spawn_yaw": robotino_spawn_yaw,
                "xarm_spawn_x": robotino_spawn_x,
                "xarm_spawn_y": robotino_spawn_y,
                "xarm_spawn_yaw": robotino_spawn_yaw,
                "robotino_gz_launch": os.path.join(
                    rto_description_share,
                    "launch",
                    "robotino_gz_wheels_table_xarm_rc2025.launch.py",
                ),
            }.items(),
        ),
        TimerAction(
            period=9.0,
            actions=[
                ExecuteProcess(
                    cmd=[
                        "ros2",
                        "topic",
                        "pub",
                        "--once",
                        "/initialpose",
                        "geometry_msgs/msg/PoseWithCovarianceStamped",
                        [
                            "{header: {frame_id: 'map'}, pose: {pose: {position: {x: ",
                            initial_pose_x,
                            ", y: ",
                            initial_pose_y,
                            ", z: 0.0}, orientation: {z: ",
                            initial_pose_yaw_z,
                            ", w: ",
                            initial_pose_yaw_w,
                            "}}, covariance: [0.25, 0.0, 0.0, 0.0, 0.0, 0.0, ",
                            "0.0, 0.25, 0.0, 0.0, 0.0, 0.0, ",
                            "0.0, 0.0, 0.0, 0.0, 0.0, 0.0, ",
                            "0.0, 0.0, 0.0, 0.0, 0.0, 0.0, ",
                            "0.0, 0.0, 0.0, 0.0, 0.0, 0.0, ",
                            "0.0, 0.0, 0.0, 0.0, 0.0, 0.06853891945200942]}}",
                        ],
                    ],
                    output="screen",
                ),
            ],
        ),
    ])
