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
                'use_sim_time': False,
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
                'use_sim_time': False,
                'set_initial_pose': True,
                'initial_pose.x': 0.0,
                'initial_pose.y': 0.0,
                'initial_pose.yaw': 0.0,
                
                # Particle filter settings (reduced for performance)
                'min_particles': 100,
                'max_particles': 500,
                'recovery_alpha_slow': 0.0,
                'recovery_alpha_fast': 0.0,
                
                # CRITICAL: Robot model - OMNIDIRECTIONAL
                'odom_model_type': 'omni',
                # Omni model has 5 noise parameters (diff has only 4)
                'odom_alpha1': 0.05,   # Rotation noise from rotation
                'odom_alpha2': 0.05,   # Rotation noise from translation  
                'odom_alpha3': 0.05,   # Translation noise from translation
                'odom_alpha4': 0.05,   # Translation noise from rotation
                'odom_alpha5': 0.03,   # Translation noise from strafing (OMNI ONLY)
                
                # Update thresholds - more aggressive
                'update_min_d': 0.05,    # Update after 5cm movement (was 0.1)
                'update_min_a': 0.1,     # Update after 0.1rad rotation (was 0.2)
                'resample_interval': 2,  # Resample every 2 updates
                
                # Laser model - optimized for likelihood_field
                'laser_model_type': 'likelihood_field',
                'laser_likelihood_max_dist': 2.0,
                'laser_min_range': 0.1,
                'laser_max_range': 30.0,
                
                # Frame IDs - VERIFY THESE MATCH YOUR TF TREE
                'base_frame_id': 'base_link',
                'odom_frame_id': 'odom',
                'global_frame_id': 'map',
                
                # TF settings
                'tf_broadcast': True,
                'transform_tolerance': 1.0,
                
                # Sensor settings
                'laser_z_hit': 0.95,
                'laser_z_rand': 0.05,
                'laser_sigma_hit': 0.2,
                
                # Selective resampling (improves performance)
                'selective_resampling': True
            }]
        ),
        # Lifecycle Manager
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
        
        # RViz with nav2 config
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            parameters=[{'use_sim_time': False}],
            arguments=['-d', rviz_config_path]
        )
    ])