Robotino Navigation with ROS 2 (Webots + Real Robot)

This repository provides a unified ROS 2 navigation stack for Festo Robotino, designed to run unchanged core logic across:

✅ Webots simulation (Robotino + LiDAR + Nav2)

✅ Real Robotino hardware using Nav2 + AMCL

✅ Low-level tools for debugging odometry vs. laser, and experimenting with virtual attractors / potential fields

The guiding principle of this repo is:

Same navigation pipeline, same behaviors — only launch files and parameters change between simulation and real robot.

Repository Structure (Current)
robotino_ros2_ws/
├── src/
│   ├── robotino_webots/
│   │   ├── worlds/            # Webots worlds (apartment, lab, test maps)
│   │   ├── description/       # Robotino URDF / Xacro (LiDAR, camera, frames)
│   │   ├── launch/
│   │   │   ├── sim/           # Webots simulation launches
│   │   │   ├── nav2/          # Nav2 bringup (sim + real)
│   │   │   └── real/          # Real Robotino bringup
│   │   └── config/            # Nav2, AMCL, controller params
│   │
│   ├── robotino_bts/           # Behavior Trees (py_trees / Nav2 actions)
│   │   ├── trees/
│   │   ├── behaviors/
│   │   └── launch/
│   │
│   ├── vision/                 # Camera, YOLO, segmentation, services
│   │   ├── launch/
│   │   └── nodes/
│   │
│   ├── robot_movement/         # Potential fields, attractors, helpers
│   │
│   └── robotino_interfaces/    # Custom ROS 2 messages/services
│
├── install/
├── build/
└── log/


⚠️ Note
Older references to ROS 1, deprecated navigation stacks, or duplicated bringup logic have been removed.
Navigation is Nav2-only, both in simulation and on the real robot.

Key Design Decisions

Nav2 everywhere
No forked logic between sim and real — only parameter files and topic remaps differ.

Webots as first-class citizen
Webots is used not just for visualization, but for:

Odometry debugging

AMCL tuning

Costmap validation

Behavior Tree testing

Behavior Trees at task level
High-level behaviors live in robotino_bts, decoupled from:

Localization source (AMCL)

Planner/controller choice

Simulation vs. hardware

Explicit debugging tools
Nodes and launch files exist specifically to:

Compare odom vs laser consistency

Visualize navigation failures

Test artificial attractors / fields independently of Nav2

Simulation vs. Real Robot
Component	Simulation (Webots)	Real Robotino
Localization	AMCL	AMCL
Navigation	Nav2	Nav2
Robot Description	Same URDF/Xacro	Same
Behaviors	Same BTs	Same
Difference	Launch + params	Launch + params
Status

✔ Webots navigation stable

✔ Real robot navigation working with AMCL

✔ TF tree aligned between sim and real

✔ Behavior Trees reusable across platforms

This repository is actively used for research, teaching, and RoboCup-style domestic robotics tasks, and is intentionally kept minimal, explicit, and debuggable.
