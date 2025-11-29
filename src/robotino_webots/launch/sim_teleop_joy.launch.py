from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():

    # HARD-CODED PATH TO SOURCE YAML
    config_file = '/home/oscar/robotino_ros2_ws/src/robotino_webots/config/teleop_joy_robotino.yaml'

    print(f"Using teleop config: {config_file}")

    return LaunchDescription([
        # JOYSTICK DRIVER
        Node(
            package='joy',
            executable='joy_node',
            name='joy_node',
            output='screen',
            parameters=[
                {'device': '/dev/input/js0'},
                {'deadzone': 0.05},
                {'autorepeat_rate': 20.0},
            ],
        ),

        # TELEOP TWIST JOY
        Node(
            package='teleop_twist_joy',
            executable='teleop_node',
            name='teleop_twist_joy',
            output='screen',
            parameters=[config_file],
            remappings=[
                ('cmd_vel', '/cmd_vel'),
            ],
        ),
    ])
