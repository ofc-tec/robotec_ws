# Robotino Navigation with ROS 2 + Webots + Real Robot

This repository contains a **ROS 2 navigation stack for Robotino**, supporting:

- ✅ **Webots simulation** (Robotino + LiDAR + Nav2)
- ✅ **Real Robotino navigation** with Nav2 and AMCL
- ✅ Tools for debugging **odometry vs. laser** and testing virtual attractors / potential fields

The goal is to have the *same* navigation pipeline running in both **simulation** and **real hardware**, changing only launch files and a few parameters (map, topics, etc.).

---

## 1. Repository Layout

Typical layout (you may adjust this section to match your exact tree):

```text
robotino_ros2_ws/
├── src/
│   ├── robotino_webots/       # Webots world, robot description, bridge/bringup, nav2 launches
│   └── robot_movement/        # Line detector, potential fields, helper nodes
├── install/
├── build/
└── log/
