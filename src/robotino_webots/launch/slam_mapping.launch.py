from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess, DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Get package share directories
    slam_toolbox_share = get_package_share_directory('slam_toolbox')
    
    # Launch arguments
    world_file = LaunchConfiguration('world_file')
    
    return LaunchDescription([
        # Launch argument for world file
        DeclareLaunchArgument(
            'world_file',
            default_value='/home/oscar/simple_slam_world.wbt',
            description='Path to Webots world file'
        ),
        
        # Webots world
        ExecuteProcess(
            cmd=['webots', world_file],
            output='screen'
        ),
        
        # Robot controller - wait 10 seconds for Webots to load
        Node(
            package='robotino_webots',
            executable='robotino_webots_controller.py',
            name='robotino_controller',
            output='screen',
            parameters=[{'use_sim_time': True}],
            # Add delay via execute process if needed, or rely on controller's retry logic
        ),
        
        # SLAM toolbox - USE THE WORKING LAUNCH FILE
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                slam_toolbox_share,
                '/launch/online_async_launch.py'
            ]),
            launch_arguments={
                'use_sim_time': 'true'
            }.items()
        ),
        
        # RViz2
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            parameters=[{'use_sim_time': True}]
        )
    ])