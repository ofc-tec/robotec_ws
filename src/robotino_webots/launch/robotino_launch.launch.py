#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Get package share directories
    #nav2_bringup_share = get_package_share_directory('nav2_bringup')
    
    # Use expanduser for home directory paths
    map_path = os.path.expanduser('~/robotino_ros2_ws/map_2.yaml')
    rviz_config_path = os.path.expanduser('~/.rviz2/amcl_robotino.rviz')
    
    return LaunchDescription([
        # Map Server
        Node(
            package='nav2_map_server',
            executable='map_server',
            name='map_server',
            output='screen',
            parameters=[{
                'use_sim_time': True,  # CHANGED TO TRUE
                'yaml_filename': map_path,
                'frame_id': 'map'
            }]
        ),
        
        # AMCL                   
        Node(
            package='nav2_amcl',
            executable='amcl',
            name='amcl',
            output='screen',
            parameters=[{
                # Basic setup
                'use_sim_time': True,  # CHANGED TO TRUE
                'set_initial_pose': True,
                'initial_pose.x': 0.0,
                'initial_pose.y': 0.0,
                'initial_pose.yaw': 0.0,
                
                # ... rest of your AMCL parameters remain the same
            }]
        ),
        
        # Lifecycle Manager
        Node(
            package='nav2_lifecycle_manager',
            executable='lifecycle_manager',
            name='lifecycle_manager',
            output='screen',
            parameters=[{
                'use_sim_time': True,  # CHANGED TO TRUE
                'autostart': True,
                'node_names': ['map_server', 'amcl']
            }]
        ),
        
        # RViz with nav2 config
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            parameters=[{'use_sim_time': True}],  # CHANGED TO TRUE
            arguments=['-d', rviz_config_path]
        )
    ])