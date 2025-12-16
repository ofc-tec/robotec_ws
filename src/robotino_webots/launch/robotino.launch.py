#!/usr/bin/env python3
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.substitutions import LaunchConfiguration
from launch.launch_description_sources import PythonLaunchDescriptionSource
from ament_index_python.packages import get_package_share_directory
import os


def generate_launch_description():
    robotino_webots_share = get_package_share_directory('robotino_webots')

    # Paths to existing launches
    nav_launch = os.path.join(robotino_webots_share, 'launch', 'nav_robotino.launch.py')
    vision_launch = os.path.join(robotino_webots_share, 'launch', 'vision.launch.py')

    # Exposed launch arguments (defaults mirror the originals)
    world_file = LaunchConfiguration('world_file')
    map_file = LaunchConfiguration('map_file')
    use_sim_time = LaunchConfiguration('use_sim_time')
    image_topic = LaunchConfiguration('image_topic')
    cloud_topic = LaunchConfiguration('cloud_topic')

    declare_world = DeclareLaunchArgument(
        'world_file',
        default_value=os.path.join(robotino_webots_share, 'worlds', 'robotino_apartment.wbt'),
        description='Path to Webots world file'
    )

    declare_map = DeclareLaunchArgument(
        'map_file',
        default_value=os.path.expanduser('~/robotino_ros2_ws/map_2.yaml'),
        description='Path to map YAML file'
    )

    declare_sim_time = DeclareLaunchArgument(
        'use_sim_time',
        default_value='false',
        description='Use simulation time'
    )

    declare_image_topic = DeclareLaunchArgument(
        'image_topic',
        default_value='/kinect/rgb/image_raw',
        description='RGB image topic for vision nodes'
    )

    declare_cloud_topic = DeclareLaunchArgument(
        'cloud_topic',
        default_value='/kinect/depth/points',
        description='Depth pointcloud topic'
    )

    # Include the nav and vision launch files, forwarding args
    include_nav = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(nav_launch),
        launch_arguments={
            'world_file': world_file,
            'map_file': map_file,
            'use_sim_time': use_sim_time
        }.items()
    )

    include_vision = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(vision_launch),
        launch_arguments={
            'image_topic': image_topic,
            'cloud_topic': cloud_topic
        }.items()
    )

    return LaunchDescription([
        declare_world,
        declare_map,
        declare_sim_time,
        declare_image_topic,
        declare_cloud_topic,
        include_nav,
        include_vision,
    ])
