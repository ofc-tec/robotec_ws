#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition
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
    rgb_topic = LaunchConfiguration('rgb_topic')
    depth_topic = LaunchConfiguration('depth_topic')
    camera_info_topic = LaunchConfiguration('camera_info_topic')
    rtabmap_db_path = LaunchConfiguration('rtabmap_db_path')
    incremental_memory = LaunchConfiguration('incremental_memory')
    init_wm_with_all_nodes = LaunchConfiguration('init_wm_with_all_nodes')
    subscribe_scan = LaunchConfiguration('subscribe_scan')
    reg_strategy = LaunchConfiguration('reg_strategy')
    grid_sensor = LaunchConfiguration('grid_sensor')
    enable_loger = LaunchConfiguration('enable_loger')
    loger_csv_path = LaunchConfiguration('loger_csv_path')

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

    camera_info = Node(
        package='robotino_webots',
        executable='kinect_camera_info_publisher.py',
        name='kinect_camera_info_publisher',
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'rgb_camera_info_topic': camera_info_topic,
            'depth_camera_info_topic': LaunchConfiguration('depth_camera_info_topic'),
            'frame_id': LaunchConfiguration('camera_frame_id'),
            'width': 640,
            'height': 480,
            'hfov': 1.047,
            'publish_rate': 15.0,
        }],
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
            'subscribe_scan': ParameterValue(subscribe_scan, value_type=bool),
            'subscribe_rgb': True,
            'subscribe_depth': True,
            'subscribe_stereo': False,
            'approx_sync': True,
            'topic_queue_size': 30,
            'sync_queue_size': 30,
            'queue_size': 30,
            'Reg/Strategy': ParameterValue(reg_strategy, value_type=str),
            'Reg/Force3DoF': 'true',
            'Reg/RepeatOnce': 'true',
            'RGBD/ProximityBySpace': 'true',
            'RGBD/ProximityByTime': 'false',
            'RGBD/ProximityOdomGuess': 'true',
            'RGBD/ProximityPathMaxNeighbors': '10',
            'RGBD/NeighborLinkRefining': 'true',
            'Grid/Sensor': ParameterValue(grid_sensor, value_type=str),
            'Grid/RangeMin': '0.05',
            'Grid/RangeMax': '10.0',
            'Grid/CellSize': '0.05',
            'Icp/Force4DoF': 'true',
            'Icp/MaxCorrespondenceDistance': '0.2',
            'Icp/CorrespondenceRatio': '0.05',
            'Icp/VoxelSize': '0.03',
            'Vis/MinInliers': '12',
            'Vis/FeatureType': '8',
            'Mem/IncrementalMemory': ParameterValue(incremental_memory, value_type=str),
            'Mem/InitWMWithAllNodes': ParameterValue(init_wm_with_all_nodes, value_type=str),
        }],
        remappings=[
            ('rgb/image', rgb_topic),
            ('depth/image', depth_topic),
            ('rgb/camera_info', camera_info_topic),
            ('scan', scan_topic),
            ('odom', odom_topic),
        ],
    )


    loger = Node(
        package='robotino_webots',
        executable='loger.py',
        name='loger',
        output='screen',
        condition=IfCondition(enable_loger),
        parameters=[{
            'use_sim_time': use_sim_time,
            'odom_topic': odom_topic,
            'map_frame': map_frame_id,
            'odom_frame': odom_frame_id,
            'base_frame': frame_id,
            'log_period_sec': 1.0,
            'csv_path': loger_csv_path,
        }],
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
            'subscribe_scan': ParameterValue(subscribe_scan, value_type=bool),
            'subscribe_rgb': True,
            'subscribe_depth': True,
            'approx_sync': True,
            'topic_queue_size': 30,
            'sync_queue_size': 30,
        }],
        remappings=[
            ('rgb/image', rgb_topic),
            ('depth/image', depth_topic),
            ('rgb/camera_info', camera_info_topic),
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
        DeclareLaunchArgument('use_sim_time', default_value='false'),
        DeclareLaunchArgument('frame_id', default_value='base_footprint'),
        DeclareLaunchArgument('odom_frame_id', default_value='odom'),
        DeclareLaunchArgument('map_frame_id', default_value='map'),
        DeclareLaunchArgument('scan_topic', default_value='/scan'),
        DeclareLaunchArgument('odom_topic', default_value='/odom'),
        DeclareLaunchArgument('rgb_topic', default_value='/kinect_sim/rgb/image_raw'),
        DeclareLaunchArgument('depth_topic', default_value='/kinect_sim/depth/image_raw'),
        DeclareLaunchArgument('camera_info_topic', default_value='/kinect_sim/rgb/camera_info'),
        DeclareLaunchArgument('depth_camera_info_topic', default_value='/kinect_sim/depth/camera_info'),
        DeclareLaunchArgument('camera_frame_id', default_value='kinect_link'),
        DeclareLaunchArgument('rtabmap_db_path', default_value='~/.ros/robotino_webots_rtabmap_rgbd.db'),
        DeclareLaunchArgument('incremental_memory', default_value='false'),
        DeclareLaunchArgument('init_wm_with_all_nodes', default_value='true'),
        DeclareLaunchArgument('subscribe_scan', default_value='true'),
        DeclareLaunchArgument('reg_strategy', default_value='2'),
        DeclareLaunchArgument('grid_sensor', default_value='2'),
        DeclareLaunchArgument('enable_loger', default_value='true'),
        DeclareLaunchArgument('loger_csv_path', default_value='~/.ros/robotino_rtabmap_correction_log.csv'),
        robotino_min,
        camera_info,
        TimerAction(period=3.0, actions=[rtabmap]),
        TimerAction(period=4.0, actions=[rtabmap_viz]),
        TimerAction(period=5.0, actions=[loger]),
    ])
