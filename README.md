# Robotec WS — Minimal Setup

This repository contains a minimal ROS 2 + Webots setup for Robotino.

----------------------------------------

Minimal Test

1. Clone the repository

cd ~/robotec_ws/src
git clone https://github.com/ofc-tec/robotec_ws.git

----------------------------------------

2. Build

cd ~/robotec_ws
colcon build

----------------------------------------

3. Source

source install/setup.bash

(Do this in every new terminal)

----------------------------------------

4. Launch Robotino (Webots)

ros2 launch robotino_webots robotino_min.launch.py

----------------------------------------

5. Run Vision Node

ros2 run vision vision_node_min --ros-args -p image_topic:=/kinect_sim/rgb/image_raw

----------------------------------------

6. Send Test Command

ros2 topic pub -1 /cmd_vel geometry_msgs/msg/Twist "{linear: {x: 0.0}, angular: {z: 0.0}}"

----------------------------------------

Expected Behavior

- Webots launches Robotino
- Vision window shows camera feed
- /cmd_vel accepts commands

----------------------------------------

Notes

- If nothing moves:
  ros2 topic info /cmd_vel

- If image does not appear:
  ros2 topic list

----------------------------------------

Goal

Minimal pipeline test:

Sensors → Vision → ROS2 → Control
