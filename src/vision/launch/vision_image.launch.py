from launch import LaunchDescription
from launch_ros.actions import Node
from launch.actions import DeclareLaunchArgument
from launch.substitutions import LaunchConfiguration


def generate_launch_description():
    image_topic_arg = DeclareLaunchArgument(
        'image_topic',
        default_value='/camera/image_raw',
        description='Image topic to subscribe to.',
    )

    pointcloud_topic_arg = DeclareLaunchArgument(
        'pointcloud_topic',
        default_value='',
        description='PointCloud2 topic (leave empty to disable).',
    )

    image_topic = LaunchConfiguration('image_topic')
    pointcloud_topic = LaunchConfiguration('pointcloud_topic')

    vision_node = Node(
        package='vision',
        executable='vision_node',
        name='vision_node',
        output='screen',
        parameters=[
            {
                'image_topic': image_topic,
                'pointcloud_topic': pointcloud_topic,
            }
        ],
    )

    return LaunchDescription([
        image_topic_arg,
        pointcloud_topic_arg,
        vision_node,
    ])
