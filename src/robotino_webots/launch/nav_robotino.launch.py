from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import ExecuteProcess, DeclareLaunchArgument, TimerAction
from launch.substitutions import LaunchConfiguration
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():
    # Get package directories
    robotino_webots_share = get_package_share_directory('robotino_webots')
    nav2_bringup_share = get_package_share_directory('nav2_bringup')
    
    # Launch arguments
    world_file = LaunchConfiguration('world_file')
    map_file = LaunchConfiguration('map_file')
    use_sim_time = LaunchConfiguration('use_sim_time', default='true')
    
    # Load robot URDF
    urdf_path = os.path.join(robotino_webots_share, 'urdf', 'Robotino3.urdf')
    with open(urdf_path, 'r') as f:
        robot_description = f.read()
    
    # Nav2 params file
    nav2_params_path = os.path.join(nav2_bringup_share, 'params', 'nav2_params.yaml')
    
    return LaunchDescription([

        
        # Launch arguments
        DeclareLaunchArgument(
            'world_file',
            default_value=os.path.join(robotino_webots_share, 'worlds', 'robotino_apartment.wbt'),
            description='Path to Webots world file'
        ),
        DeclareLaunchArgument(
            'map_file',
            default_value=os.path.expanduser('~/robotino_ros2_ws/map_2.yaml'),
            description='Path to map YAML file'
        ),
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='true',
            description='Use simulation time'
        ),
        
        # 1. Webots simulation
        ExecuteProcess(
            cmd=['webots', world_file],
            output='screen'
        ),
        
        # 2. Robot controller (delayed start)
        TimerAction(
            period=5.0,
            actions=[
                Node(
                    package='robotino_webots',
                    executable='robotino_webots_controller.py',
                    name='robotino_controller',
                    output='screen',
                    parameters=[{'use_sim_time': use_sim_time}],
                )
            ]
        ),
        
        # 3. Robot state publisher
        TimerAction(
            period=6.0,
            actions=[
                Node(
                    package='robot_state_publisher',
                    executable='robot_state_publisher',
                    name='robot_state_publisher',
                    output='screen',
                    parameters=[{
                        'robot_description': robot_description,
                        'use_sim_time': use_sim_time,
                        'publish_frequency': 30.0
                    }]
                )
            ]
        ),
        
        # 4. Static transform: map -> odom (CRITICAL for Nav2 bootstrap)
        TimerAction(
            period=7.0,
            actions=[
                Node(
                    package='tf2_ros',
                    executable='static_transform_publisher',
                    name='map_to_odom',
                    arguments=['0', '0', '0', '0', '0', '0', 'map', 'odom']
                )
            ]
        ),
        
        # 5. Map server with frame_id fix (CRITICAL)
        TimerAction(
            period=8.0,
            actions=[
                Node(
                    package='nav2_map_server',
                    executable='map_server',
                    name='map_server',
                    output='screen',
                    parameters=[{
                        'use_sim_time': use_sim_time,
                        'yaml_filename': map_file,
                        'frame_id': 'map'  # FIXES THE EMPTY FRAME_ID BUG
                    }]
                )
            ]
        ),
        
        # 6. AMCL localization
        TimerAction(
            period=10.0,
            actions=[
              Node(
            package='nav2_amcl',
            executable='amcl',
            name='amcl',
            output='screen',
            parameters=[{
                'use_sim_time': use_sim_time,
                
                # Particle settings
                'min_particles': 500,
                'max_particles': 2000,
                
                # 🚀 CRITICAL: REDUCE UPDATE FREQUENCY
                'transform_tolerance': 2.0,      # Increased tolerance
                'update_min_d': 0.05,            # UPDATE AFTER 5cm (not 1cm)
                'update_min_a': 0.15,            # UPDATE AFTER 8.6° (not 1.7°)
                
                # Laser settings  
                'laser_min_range': 0.05,
                'laser_max_range': 10.0,
                'laser_max_beams': 30,
                
                # Odometry smoothing
                'odom_alpha1': 0.5,
                'odom_alpha2': 0.5, 
                'odom_alpha3': 0.5,
                'odom_alpha4': 0.5,
                
                # Recovery behavior
                'recovery_alpha_slow': 0.001,
                'recovery_alpha_fast': 0.1,
                
                # Laser model
                'laser_model_type': 'likelihood_field',
                'laser_likelihood_max_dist': 2.0,
                
                # Initial pose
                'set_initial_pose': True,
                'initial_pose.x': 0.0,
                'initial_pose.y': 0.0,
                'initial_pose.theta': 0.0
            }]
        )                            
            ]
        ),
        #
        # 7. Controller server
        TimerAction(
            period=12.0,
            actions=[
                Node(
                    package='nav2_controller',
                    executable='controller_server',
                    name='controller_server',
                    output='screen',
                    parameters=[nav2_params_path, {'use_sim_time': use_sim_time}]
                )
            ]
        ),
        
        # 8. Planner server
        TimerAction(
            period=14.0,
            actions=[
                Node(
                    package='nav2_planner',
                    executable='planner_server',
                    name='planner_server',
                    output='screen',
                    parameters=[nav2_params_path, {'use_sim_time': use_sim_time,                'local_costmap.obstacle_layer.observation_persistence': 0.0}]
                )
            ]
        ),
        
        # 9. Behavior server (for recovery behaviors)
        TimerAction(
            period=16.0,
            actions=[
                Node(
                    package='nav2_behaviors',
                    executable='behavior_server',
                    name='behavior_server',
                    output='screen',
                    parameters=[{'use_sim_time': use_sim_time}]
                )
            ]
        ),
        
        # 10. BT Navigator
        TimerAction(
            period=18.0,
            actions=[
                Node(
                    package='nav2_bt_navigator',
                    executable='bt_navigator',
                    name='bt_navigator',
                    output='screen',
                    parameters=[nav2_params_path, {'use_sim_time': use_sim_time}]
                )
            ]
        ),
        
        # 11. Lifecycle manager to activate all Nav2 nodes
        TimerAction(
            period=20.0,
            actions=[
                Node(
                    package='nav2_lifecycle_manager',
                    executable='lifecycle_manager',
                    name='lifecycle_manager_navigation',
                    output='screen',
                    parameters=[{
                        'use_sim_time': use_sim_time,
                        'autostart': True,
                        'node_names': [
                            'map_server',
                            'amcl', 
                            'controller_server',
                            'planner_server',
                            'behavior_server',
                            'bt_navigator'
                        ]
                    }]
                )
            ]
        ),
        
        # 12. RViz (delayed for everything to be ready)
        TimerAction(
            period=25.0,
            actions=[
                Node(
                    package='rviz2',
                    executable='rviz2',
                    name='rviz2',
                    parameters=[{'use_sim_time': use_sim_time}],
                    arguments=['-d', os.path.join(nav2_bringup_share, 'rviz', 'nav2_default_view.rviz')]
                )
            ]
        )
    ])