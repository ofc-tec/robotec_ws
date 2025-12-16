from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, ExecuteProcess
from launch.substitutions import LaunchConfiguration
from launch.conditions import IfCondition
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    pkg = get_package_share_directory("robotino_bts")
    config_path = os.path.join(pkg, "config", "known_locations.yaml")

    with_viewer = LaunchConfiguration("with_viewer")

    return LaunchDescription([
        DeclareLaunchArgument(
            "with_viewer",
            default_value="false",
            description="Start py_trees_ros_viewer GUI (py-trees-tree-viewer)"
        ),

        # (kept) your existing BT executor
        Node(
            package="robotino_bts",
            executable="task_manager",
            name="bt_executor",
            output="screen",
            parameters=[{"known_locations": config_path}],
        ),

        # (added) known_locations_server
        Node(
            package="known_locations_tf_server",
            executable="known_locations_server",
            name="known_locations_server",
            output="screen",
        ),

        # (added, optional) PyTrees GUI Viewer
        ExecuteProcess(
            condition=IfCondition(with_viewer),
            cmd=["py-trees-tree-viewer"],
            output="screen",
        ),
    ])
