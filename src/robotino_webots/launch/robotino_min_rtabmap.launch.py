#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')
    frame_id = LaunchConfiguration('frame_id')
    odom_frame_id = LaunchConfiguration('odom_frame_id')
    map_frame_id = LaunchConfiguration('map_frame_id')
    scan_topic = LaunchConfiguration('scan_topic')
    odom_topic = LaunchConfiguration('odom_topic')
    rtabmap_db_path = LaunchConfiguration('rtabmap_db_path')
    incremental_memory = LaunchConfiguration('incremental_memory')
    init_wm_with_all_nodes = LaunchConfiguration('init_wm_with_all_nodes')
    proximity_global_scan_map = LaunchConfiguration('proximity_global_scan_map')
    icp_max_translation = LaunchConfiguration('icp_max_translation')
    icp_max_rotation = LaunchConfiguration('icp_max_rotation')
    icp_max_correspondence_distance = LaunchConfiguration('icp_max_correspondence_distance')
    icp_correspondence_ratio = LaunchConfiguration('icp_correspondence_ratio')

    robotino_min = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(
            PathJoinSubstitution([
                FindPackageShare('robotino_webots'),
                'launch',
                'robotino_min.launch.py',
            ])
        ),
        launch_arguments={
            'world_file': LaunchConfiguration('world_file'),
        }.items(),
    )

    rtabmap = Node(
        package='rtabmap_slam',
        executable='rtabmap',
        name='rtabmap',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'frame_id': frame_id,
            'odom_frame_id': odom_frame_id,
            'map_frame_id': map_frame_id,
            'database_path': rtabmap_db_path,
            'subscribe_scan': True,
            'subscribe_rgb': False,
            'subscribe_depth': False,
            'subscribe_stereo': False,
            'approx_sync': True,
            'topic_queue_size': 30,
            'sync_queue_size': 30,
            'queue_size': 30,
            'Reg/Strategy': '1',
            'Reg/Force3DoF': 'true',
            'Reg/RepeatOnce': 'true',
            'RGBD/LinearUpdate': '0.08',
            'RGBD/AngularUpdate': '0.08',
            'RGBD/ProximityBySpace': 'true',
            'RGBD/ProximityByTime': 'false',
            'RGBD/ProximityOdomGuess': 'true',
            'RGBD/ProximityAngle': '90',
            'RGBD/ProximityMaxGraphDepth': '0',
            'RGBD/ProximityMaxPaths': '0',
            'RGBD/ProximityPathFilteringRadius': '0.5',
            'RGBD/ProximityPathMaxNeighbors': '10',
            'RGBD/ProximityGlobalScanMap': ParameterValue(proximity_global_scan_map, value_type=str),
            'RGBD/NeighborLinkRefining': 'true',
            'RGBD/OptimizeFromGraphEnd': 'false',
            'Rtabmap/LoopThr': '0.08',
            'Rtabmap/LoopRatio': '0',
            'Grid/FromDepth': 'false',
            'Grid/Sensor': '0',
            'Grid/RangeMin': '0.05',
            'Grid/RangeMax': '10.0',
            'Grid/CellSize': '0.05',
            'Grid/Scan2dUnknownSpaceFilled': 'true',
            'Icp/Force4DoF': 'true',
            'Icp/PointToPlane': 'false',
            'Icp/MaxTranslation': ParameterValue(icp_max_translation, value_type=str),
            'Icp/MaxRotation': ParameterValue(icp_max_rotation, value_type=str),
            'Icp/MaxCorrespondenceDistance': ParameterValue(icp_max_correspondence_distance, value_type=str),
            'Icp/CorrespondenceRatio': ParameterValue(icp_correspondence_ratio, value_type=str),
            'Icp/VoxelSize': '0.02',
            'Icp/RangeMin': '0.05',
            'Icp/RangeMax': '10.0',
            'Mem/IncrementalMemory': ParameterValue(incremental_memory, value_type=str),
            'Mem/InitWMWithAllNodes': ParameterValue(init_wm_with_all_nodes, value_type=str),
        }],
        remappings=[
            ('scan', scan_topic),
            ('odom', odom_topic),
        ],
    )

    rtabmap_viz = Node(
        package='rtabmap_viz',
        executable='rtabmap_viz',
        name='rtabmap_viz',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'frame_id': frame_id,
            'odom_frame_id': odom_frame_id,
            'subscribe_scan': True,
            'subscribe_rgb': False,
            'subscribe_depth': False,
            'approx_sync': True,
        }],
        remappings=[
            ('scan', scan_topic),
            ('odom', odom_topic),
        ],
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'world_file',
            default_value=PathJoinSubstitution([
                FindPackageShare('robotino_webots'),
                'worlds',
                'robotino_apartment.wbt',
            ]),
            description='Webots world file passed through to robotino_min.',
        ),
        DeclareLaunchArgument(
            'use_sim_time',
            default_value='false',
            description='Keep false to match robotino_min unless /clock is added.',
        ),
        DeclareLaunchArgument(
            'frame_id',
            default_value='base_footprint',
            description='Robot base frame used by RTAB-Map.',
        ),
        DeclareLaunchArgument(
            'odom_frame_id',
            default_value='odom',
            description='Odometry frame used by Robotino Webots controller.',
        ),
        DeclareLaunchArgument(
            'map_frame_id',
            default_value='map',
            description='Map frame published by RTAB-Map.',
        ),
        DeclareLaunchArgument(
            'scan_topic',
            default_value='/scan',
            description='Laser scan topic from robotino_webots_controller.py.',
        ),
        DeclareLaunchArgument(
            'odom_topic',
            default_value='/odom',
            description='Odometry topic from robotino_webots_controller.py.',
        ),
        DeclareLaunchArgument(
            'rtabmap_db_path',
            default_value='~/.ros/robotino_webots_rtabmap.db',
            description='RTAB-Map database path.',
        ),
        DeclareLaunchArgument(
            'incremental_memory',
            default_value='true',
            description='true=mapping mode, false=localization mode.',
        ),
        DeclareLaunchArgument(
            'init_wm_with_all_nodes',
            default_value='false',
            description='Load all previous database nodes into working memory, useful for localization.',
        ),
        DeclareLaunchArgument(
            'proximity_global_scan_map',
            default_value='false',
            description='Use a global assembled laser scan map for one-to-many proximity detection in localization mode.',
        ),
        DeclareLaunchArgument(
            'icp_max_translation',
            default_value='1.0',
            description='Maximum accepted ICP translation correction in meters.',
        ),
        DeclareLaunchArgument(
            'icp_max_rotation',
            default_value='3.14',
            description='Maximum accepted ICP rotation correction in radians.',
        ),
        DeclareLaunchArgument(
            'icp_max_correspondence_distance',
            default_value='0.35',
            description='Maximum distance for ICP point correspondences.',
        ),
        DeclareLaunchArgument(
            'icp_correspondence_ratio',
            default_value='0.05',
            description='Minimum ICP correspondence ratio required to accept a transform.',
        ),
        robotino_min,
        TimerAction(period=3.0, actions=[rtabmap]),
        TimerAction(period=4.0, actions=[rtabmap_viz]),
    ])
