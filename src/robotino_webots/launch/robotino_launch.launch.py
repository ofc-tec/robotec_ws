#!/usr/bin/env python3

from launch import LaunchDescription
from launch_ros.actions import Node
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    # Use expanduser for home directory paths
    map_path = os.path.expanduser('~/robotino_ros2_ws/map_2.yaml')
    rviz_config_path = os.path.expanduser('~/.rviz2/amcl_robotino.rviz')

    # NEW: get this package share and point to your AMCL/Nav2 params
    pkg_share = get_package_share_directory('robotino_webots')
    amcl_params_path = os.path.join(pkg_share, 'config', 'nav2_robotino_webots.yaml')

    return LaunchDescription([
        # -------------------------------
        # Map Server  (unchanged)
        # -------------------------------
        Node(
            package='nav2_map_server',
            executable='map_server',
            name='map_server',
            output='screen',
            parameters=[{
                'use_sim_time': False,
                'yaml_filename': map_path,
                'frame_id': 'map'
            }]
        ),

        # -------------------------------
        # AMCL  (original + YAML)
        # -------------------------------
        Node(
            package='nav2_amcl',
            executable='amcl',
            name='amcl',
            output='screen',
            parameters=[
                # First load everything from your YAML:
                amcl_params_path,
                # Then override / add the same inline params you had before:
                {
                    'use_sim_time': False,
                    'publish_particle_cloud': True,
                    'min_particles': 500,
                    'max_particles': 2000,
                    'set_initial_pose': True,
                    'initial_pose.x': 0.0,
                    'initial_pose.y': 0.0,
                    'initial_pose.yaw': 0.0
                }
            ]
        ),

        # -------------------------------
        # Lifecycle Manager  (unchanged)
        # -------------------------------
        Node(
            package='nav2_lifecycle_manager',
            executable='lifecycle_manager',
            name='lifecycle_manager',
            output='screen',
            parameters=[{
                'use_sim_time': False,
                'autostart': True,
                'node_names': ['map_server', 'amcl']
            }]
        ),

        # -------------------------------
        # RViz  (unchanged)
        # -------------------------------
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            parameters=[{'use_sim_time': False}],
            arguments=['-d', rviz_config_path]
        )
    ])
