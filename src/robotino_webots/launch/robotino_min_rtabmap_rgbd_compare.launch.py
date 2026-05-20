#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription, TimerAction
from launch.conditions import IfCondition
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration, PathJoinSubstitution
from launch_ros.actions import Node
from launch_ros.parameter_descriptions import ParameterValue
from launch_ros.substitutions import FindPackageShare


def make_rtabmap_node(
    *,
    name,
    map_frame_id,
    use_sim_time,
    frame_id,
    odom_frame_id,
    rtabmap_db_path,
    rgb_topic,
    depth_topic,
    camera_info_topic,
    scan_topic,
    odom_topic,
    subscribe_scan,
    reg_strategy,
    grid_sensor,
):
    remappings = [
        ('rgb/image', rgb_topic),
        ('depth/image', depth_topic),
        ('rgb/camera_info', camera_info_topic),
        ('odom', odom_topic),
    ]
    if subscribe_scan:
        remappings.append(('scan', scan_topic))

    return Node(
        package='rtabmap_slam',
        executable='rtabmap',
        name=name,
        output='screen',
        parameters=[{
            'use_sim_time': use_sim_time,
            'frame_id': frame_id,
            'odom_frame_id': odom_frame_id,
            'map_frame_id': map_frame_id,
            'database_path': rtabmap_db_path,
            'subscribe_scan': subscribe_scan,
            'subscribe_rgb': True,
            'subscribe_depth': True,
            'subscribe_stereo': False,
            'approx_sync': True,
            'topic_queue_size': 30,
            'sync_queue_size': 30,
            'queue_size': 30,
            'Reg/Strategy': reg_strategy,
            'Reg/Force3DoF': 'true',
            'Reg/RepeatOnce': 'true',
            'RGBD/ProximityBySpace': 'true',
            'RGBD/ProximityByTime': 'false',
            'RGBD/ProximityOdomGuess': 'true',
            'RGBD/ProximityPathMaxNeighbors': '10',
            'RGBD/NeighborLinkRefining': 'true',
            'Grid/Sensor': grid_sensor,
            'Grid/RangeMin': '0.05',
            'Grid/RangeMax': '10.0',
            'Grid/CellSize': '0.05',
            'Icp/Force4DoF': 'true',
            'Icp/MaxCorrespondenceDistance': '0.2',
            'Icp/CorrespondenceRatio': '0.05',
            'Icp/VoxelSize': '0.03',
            'Vis/MinInliers': '12',
            'Vis/FeatureType': '8',
            'Mem/IncrementalMemory': 'false',
            'Mem/InitWMWithAllNodes': 'true',
        }],
        remappings=remappings,
    )


def make_loger_node(
    *,
    name,
    csv_path,
    map_frame_id,
    use_sim_time,
    frame_id,
    odom_frame_id,
    odom_topic,
    enable_loger,
):
    return Node(
        package='robotino_webots',
        executable='loger.py',
        name=name,
        output='screen',
        condition=IfCondition(enable_loger),
        parameters=[{
            'use_sim_time': use_sim_time,
            'odom_topic': odom_topic,
            'map_frame': map_frame_id,
            'odom_frame': odom_frame_id,
            'base_frame': frame_id,
            'log_period_sec': 1.0,
            'csv_path': csv_path,
        }],
    )


def generate_launch_description():
    use_sim_time = LaunchConfiguration('use_sim_time')
    frame_id = LaunchConfiguration('frame_id')
    odom_frame_id = LaunchConfiguration('odom_frame_id')
    scan_topic = LaunchConfiguration('scan_topic')
    odom_topic = LaunchConfiguration('odom_topic')
    rgb_topic = LaunchConfiguration('rgb_topic')
    depth_topic = LaunchConfiguration('depth_topic')
    camera_info_topic = LaunchConfiguration('camera_info_topic')
    lidar_rtabmap_db_path = LaunchConfiguration('lidar_rtabmap_db_path')
    visual_rtabmap_db_path = LaunchConfiguration('visual_rtabmap_db_path')
    enable_loger = LaunchConfiguration('enable_loger')

    map_frame_lidar = LaunchConfiguration('map_frame_lidar')
    map_frame_visual = LaunchConfiguration('map_frame_visual')
    lidar_log_csv_path = LaunchConfiguration('lidar_log_csv_path')
    visual_log_csv_path = LaunchConfiguration('visual_log_csv_path')

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

    lidar_rtabmap = make_rtabmap_node(
        name='rtabmap_lidar_rgbd',
        map_frame_id=map_frame_lidar,
        use_sim_time=use_sim_time,
        frame_id=frame_id,
        odom_frame_id=odom_frame_id,
        rtabmap_db_path=lidar_rtabmap_db_path,
        rgb_topic=rgb_topic,
        depth_topic=depth_topic,
        camera_info_topic=camera_info_topic,
        scan_topic=scan_topic,
        odom_topic=odom_topic,
        subscribe_scan=True,
        reg_strategy='2',
        grid_sensor='2',
    )

    visual_rtabmap = make_rtabmap_node(
        name='rtabmap_visual_rgbd',
        map_frame_id=map_frame_visual,
        use_sim_time=use_sim_time,
        frame_id=frame_id,
        odom_frame_id=odom_frame_id,
        rtabmap_db_path=visual_rtabmap_db_path,
        rgb_topic=rgb_topic,
        depth_topic=depth_topic,
        camera_info_topic=camera_info_topic,
        scan_topic=scan_topic,
        odom_topic=odom_topic,
        subscribe_scan=False,
        reg_strategy='0',
        grid_sensor='1',
    )

    lidar_loger = make_loger_node(
        name='loger_lidar',
        csv_path=lidar_log_csv_path,
        map_frame_id=map_frame_lidar,
        use_sim_time=use_sim_time,
        frame_id=frame_id,
        odom_frame_id=odom_frame_id,
        odom_topic=odom_topic,
        enable_loger=enable_loger,
    )

    visual_loger = make_loger_node(
        name='loger_visual',
        csv_path=visual_log_csv_path,
        map_frame_id=map_frame_visual,
        use_sim_time=use_sim_time,
        frame_id=frame_id,
        odom_frame_id=odom_frame_id,
        odom_topic=odom_topic,
        enable_loger=enable_loger,
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            'world_file',
            default_value=PathJoinSubstitution([
                FindPackageShare('robotino_webots'),
                'worlds',
                'robotino_apartment.wbt',
            ]),
        ),
        DeclareLaunchArgument('use_sim_time', default_value='false'),
        DeclareLaunchArgument('frame_id', default_value='base_footprint'),
        DeclareLaunchArgument('odom_frame_id', default_value='odom'),
        DeclareLaunchArgument('map_frame_lidar', default_value='map_lidar'),
        DeclareLaunchArgument('map_frame_visual', default_value='map_visual'),
        DeclareLaunchArgument('scan_topic', default_value='/scan'),
        DeclareLaunchArgument('odom_topic', default_value='/odom'),
        DeclareLaunchArgument('rgb_topic', default_value='/kinect_sim/rgb/image_raw'),
        DeclareLaunchArgument('depth_topic', default_value='/kinect_sim/depth/image_raw'),
        DeclareLaunchArgument('camera_info_topic', default_value='/kinect_sim/rgb/camera_info'),
        DeclareLaunchArgument('depth_camera_info_topic', default_value='/kinect_sim/depth/camera_info'),
        DeclareLaunchArgument('camera_frame_id', default_value='kinect_link'),
        DeclareLaunchArgument('lidar_rtabmap_db_path', default_value='~/.ros/robotino_webots_rtabmap_rgbd.db'),
        DeclareLaunchArgument('visual_rtabmap_db_path', default_value='~/.ros/robotino_webots_rtabmap_rgbd_visual_compare.db'),
        DeclareLaunchArgument('enable_loger', default_value='true'),
        DeclareLaunchArgument('lidar_log_csv_path', default_value='~/.ros/robotino_rtabmap_lidar_correction_log.csv'),
        DeclareLaunchArgument('visual_log_csv_path', default_value='~/.ros/robotino_rtabmap_visual_correction_log.csv'),
        robotino_min,
        camera_info,
        TimerAction(period=3.0, actions=[lidar_rtabmap, visual_rtabmap]),
        TimerAction(period=5.0, actions=[lidar_loger, visual_loger]),
    ])
