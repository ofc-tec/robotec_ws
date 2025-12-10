from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg = get_package_share_directory("robotino_bts")
    config_path = os.path.join(pkg, "config", "known_locations.yaml")

    return LaunchDescription([
        Node(
            package="robotino_bts",
            executable="task_manager",
            name="bt_executor",
            output="screen",
            parameters=[{"known_locations": config_path}]
        )
    ])
