#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    robotino_webots_share = get_package_share_directory("robotino_webots")
    rto_description_share = get_package_share_directory("rto_description")
    map_file = LaunchConfiguration("map_file")

    return LaunchDescription([
        DeclareLaunchArgument(
            "map_file",
            default_value=os.path.expanduser("~/robotino_ros2_ws/map_2.yaml"),
            description="Path to map YAML file used by Nav2/map_server.",
        ),
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource(
                os.path.join(robotino_webots_share, "launch", "robotino_gz_xarm.launch.py")
            ),
            launch_arguments={
                "gui": "true",
                "map_file": map_file,
                "gz_world_name": "robotino_rc2025_xarm",
                "robotino_gz_launch": os.path.join(
                    rto_description_share,
                    "launch",
                    "robotino_gz_wheels_table_xarm_rc2025.launch.py",
                ),
            }.items(),
        ),
    ])
