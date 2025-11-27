from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node
from launch.actions import IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os

def generate_launch_description():

    # Paths
    rto_node_share = get_package_share_directory('rto_node')
    nav2_share = get_package_share_directory('nav2_bringup')

    # Arguments
    hostname = LaunchConfiguration('hostname', default='192.168.0.1:12080')
    map_file = LaunchConfiguration(
        'map_file',
        default=os.path.join(os.path.expanduser('~'), 'maps', 'map_tec_2.yaml')
    )

    return LaunchDescription([

        # -----------------------------
        # 1) Launch Arguments
        # -----------------------------
        DeclareLaunchArgument('hostname', default_value='192.168.0.1:12080'),
        DeclareLaunchArgument('map_file'),

        # -----------------------------
        # 2) Robotino driver
        # -----------------------------
        IncludeLaunchDescription(
            PythonLaunchDescriptionSource([
                rto_node_share,
                '/launch/robotino_driver.launch.py'
            ]),
            launch_arguments={
                'hostname': hostname,
                'launch_odom_tf': 'true'
            }.items()
        ),

        # -----------------------------
        # 3) Static transforms
        # -----------------------------
        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='static_base_to_footprint',
            arguments=['0', '0', '0', '0', '0', '0', 'base_link', 'base_footprint']
        ),

        Node(
            package='tf2_ros',
            executable='static_transform_publisher',
            name='static_base_to_laser',
            arguments=['0.1', '0', '0.2', '0', '0', '0', 'base_link', 'laser']
        ),

        # -----------------------------
        # 4) Map Server (map -> frame_id)
        # -----------------------------
        Node(
            package='nav2_map_server',
            executable='map_server',
            name='map_server',
            output='screen',
            parameters=[{
                'use_sim_time': False,
                'yaml_filename': map_file,
                'frame_id': 'map'
            }]
        ),

        # -----------------------------
        # 5) AMCL Localization
        # -----------------------------
        Node(
            package='nav2_amcl',
            executable='amcl',
            name='amcl',
            output='screen',
            parameters=[{
                'use_sim_time': False,
                'global_frame_id': 'map',
                'odom_frame_id': 'odom',
                'base_frame_id': 'base_link',
                'scan_topic': 'scan',

                # Particle filter settings
                'min_particles': 500,
                'max_particles': 2000,

                # Sensor model
                'laser_model_type': 'likelihood_field',
                'laser_likelihood_max_dist': 2.0,
                'laser_max_beams': 60,

                # Motion model tuning
                'odom_alpha1': 0.5,
                'odom_alpha2': 0.5,
                'odom_alpha3': 0.5,
                'odom_alpha4': 0.5,

                # Initial pose
                'set_initial_pose': True,
                'initial_pose.x': 0.0,
                'initial_pose.y': 0.0,
                'initial_pose.theta': 0.0
            }]
        ),

        # -----------------------------
        # 6) Lifecycle Manager (localization)
        # -----------------------------
        Node(
            package='nav2_lifecycle_manager',
            executable='lifecycle_manager',
            name='lifecycle_manager_localization',
            output='screen',    
            parameters=[{
                'use_sim_time': False,
                'autostart': True,
                'node_names': ['map_server', 'amcl']
            }]
        ),

        # -----------------------------
        # 7) RViz2
        # -----------------------------
        Node(
            package='rviz2',
            executable='rviz2',
            name='rviz2',
            parameters=[{'use_sim_time': False}],
            arguments=['-d', os.path.join(nav2_share, 'rviz', 'nav2_default_view.rviz')]
        )
    ])