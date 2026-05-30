#!/usr/bin/env python3

import os

from ament_index_python.packages import get_package_share_directory
from launch import LaunchDescription
from launch.actions import DeclareLaunchArgument, IncludeLaunchDescription
from launch.launch_description_sources import PythonLaunchDescriptionSource
from launch.substitutions import LaunchConfiguration
from launch_ros.actions import Node


def generate_launch_description():
    robotino_webots_share = get_package_share_directory("robotino_webots")
    robotino_audio_share = get_package_share_directory("robotino_audio")
    rto_description_share = get_package_share_directory("rto_description")

    nav_launch = os.path.join(robotino_webots_share, "launch", "nav_robotino_gz.launch.py")
    vision_launch = os.path.join(robotino_webots_share, "launch", "vision.launch.py")
    speech_launch = os.path.join(robotino_audio_share, "launch", "speech_recog.launch.py")

    map_file = LaunchConfiguration("map_file")
    use_sim_time = LaunchConfiguration("use_sim_time")
    gui = LaunchConfiguration("gui")
    rviz = LaunchConfiguration("rviz")
    robotino_gz_launch = LaunchConfiguration("robotino_gz_launch")
    image_topic = LaunchConfiguration("image_topic")
    depth_topic = LaunchConfiguration("depth_topic")
    depth_info_topic = LaunchConfiguration("depth_info_topic")

    include_nav = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(nav_launch),
        launch_arguments={
            "map_file": map_file,
            "use_sim_time": use_sim_time,
            "gui": gui,
            "rviz": rviz,
            "robotino_gz_launch": robotino_gz_launch,
        }.items(),
    )

    include_vision = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(vision_launch),
        launch_arguments={
            "image_topic": image_topic,
            "depth_topic": depth_topic,
            "depth_info_topic": depth_info_topic,
        }.items(),
    )

    include_speech = IncludeLaunchDescription(
        PythonLaunchDescriptionSource(speech_launch),
    )

    kinect_depth_tf = Node(
        package="tf2_ros",
        executable="static_transform_publisher",
        name="kinect_depth_tf_glue",
        arguments=["0", "0", "0", "0", "0", "0", "kinect_link", "kinect_depth"],
        output="screen",
    )

    return LaunchDescription([
        DeclareLaunchArgument(
            "map_file",
            default_value=os.path.expanduser("~/robotino_ros2_ws/map_2.yaml"),
            description="Path to map YAML file",
        ),
        DeclareLaunchArgument(
            "use_sim_time",
            default_value="true",
            description="Use Gazebo simulation time",
        ),
        DeclareLaunchArgument(
            "gui",
            default_value="true",
            description="Start Gazebo GUI",
        ),
        DeclareLaunchArgument(
            "rviz",
            default_value="true",
            description="Start RViz with Nav2 view",
        ),
        DeclareLaunchArgument(
            "robotino_gz_launch",
            default_value=os.path.join(rto_description_share, "launch", "robotino_gz_wheels.launch.py"),
            description="Optional Robotino Gazebo base launch file passed through to nav_robotino_gz",
        ),
        DeclareLaunchArgument(
            "image_topic",
            default_value="/kinect_sim/rgb/image_raw",
            description="RGB image topic for vision nodes",
        ),
        DeclareLaunchArgument(
            "depth_topic",
            default_value="/kinect_sim/depth/image_raw",
            description="Depth image topic for vision nodes",
        ),
        DeclareLaunchArgument(
            "depth_info_topic",
            default_value="/kinect_sim/depth/camera_info",
            description="Depth camera info topic for 3D vision nodes",
        ),
        include_nav,
        include_vision,
        kinect_depth_tf,
        include_speech,
    ])
