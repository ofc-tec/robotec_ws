# Robotino Gazebo / xArm Runbook

This is the Gazebo Sim runbook for Robotino, Nav2, YOLO, and the xArm grasping setup used in the RC2025 table/object tests.

The original `README.md` is kept as the minimal Webots getting-started note.

## xArm Workspace

The Gazebo/xArm launch depends on packages from the separate xArm workspace:

```text
git@github.com:ofc-tec/ws_xarm.git
```

Expected local path:

```bash
~/ws_xarm
```

Build and source the xArm workspace before using the full Robotino + xArm launch:

```bash
cd ~/ws_xarm
source /opt/ros/jazzy/setup.bash
colcon build --symlink-install
source install/setup.bash
```

When using both workspaces in one terminal, source them in this order:

```bash
source /opt/ros/jazzy/setup.bash
source ~/robotino_ros2_ws/install/setup.bash
source ~/ws_xarm/install/setup.bash
```

## Quick Start

Open a new terminal and source ROS 2 plus this workspace:

```bash
cd ~/robotino_ros2_ws
source /opt/ros/jazzy/setup.bash
source install/setup.bash
```

For xArm launches, also source:

```bash
source ~/ws_xarm/install/setup.bash
```

Build after code, launch, world, or package changes:

```bash
cd ~/robotino_ros2_ws
colcon build --symlink-install
source install/setup.bash
```

For the packages normally touched during sim/vision work:

```bash
colcon build --packages-select rto_description robotino_webots vision robotino_bts --symlink-install
source install/setup.bash
```

## Full Gazebo + Robotino + xArm Test

Main integrated RC2025 launch:

```bash
ros2 launch robotino_webots robotino_gz_xarm_rc2025.launch.py
```

Headless Gazebo server, no Gazebo GUI:

```bash
ros2 launch robotino_webots robotino_gz_xarm_rc2025.launch.py gui:=false
```

Headless Gazebo and no RViz windows:

```bash
ros2 launch robotino_webots robotino_gz_xarm_rc2025.launch.py gui:=false rviz:=false xarm_rviz:=false
```

Useful launch arguments:

```bash
ros2 launch robotino_webots robotino_gz_xarm_rc2025.launch.py \
  robotino_spawn_x:=2.443 \
  robotino_spawn_y:=-0.528 \
  robotino_spawn_yaw:=-3.068 \
  yolo_confidence_threshold:=0.25
```

## Full Stack Without xArm Wrapper

Gazebo/Nav2/vision/YOLO:

```bash
ros2 launch robotino_webots robotino_gz_full.launch.py
```

Headless:

```bash
ros2 launch robotino_webots robotino_gz_full.launch.py gui:=false
```

For xArm camera topics when launching manually:

```bash
ros2 launch robotino_webots robotino_gz_full.launch.py \
  image_topic:=/camera/color/image_raw \
  depth_topic:=/camera/depth/image \
  depth_info_topic:=/camera/depth/camera_info
```

## Behavior Tree / Grasping Test

Run the full sim first. In a second terminal:

```bash
cd ~/robotino_ros2_ws
source /opt/ros/jazzy/setup.bash
source install/setup.bash
ros2 launch robotino_bts bt_task.launch.py
```

Without the py-trees viewer:

```bash
ros2 launch robotino_bts bt_task.launch.py with_viewer:=false
```

The behavior tree calls the YOLO service at `/yolo_detect`. YOLO returns object poses in `response.poses[]`.

Camera optical-frame correction used by the xArm grasping logic:

```text
corrected.x = raw.z
corrected.y = -raw.x
corrected.z = -raw.y
```

## Vision / YOLO Debug

Check that the service exists:

```bash
ros2 service list | grep yolo
```

Call YOLO once:

```bash
ros2 service call /yolo_detect robotino_interfaces/srv/YoloDetect "{}"
```

Watch image topics:

```bash
ros2 topic hz /camera/color/image_raw
ros2 topic hz /camera/depth/image
ros2 topic echo /camera/depth/camera_info --once
```

Inspect YOLO TF output:

```bash
ros2 run tf2_ros tf2_echo UF_ROBOT/link6/cameradepth bird
```

Replace `bird` with the detected class name. The vision node can also publish class-name TFs after a YOLO test trigger.

Known camera detail in this setup:

```text
RGB:   720 x 1280
Depth: 360 x 640
```

Depth/mask work must account for that scale difference.

## Useful Gazebo Object Spawn

Spawn one YCB object into the running RC2025 world:

```bash
ros2 run ros_gz_sim create \
  -world robotino_rc2025_xarm \
  -file /home/oscar/gz_models/ycb_011_banana/model-1_4.sdf \
  -name banana \
  -x 1.5 -y -0.50 -z 1.85
```

Use unique `-name` values for every spawned model.

## Common Checks

List nodes:

```bash
ros2 node list
```

List topics:

```bash
ros2 topic list
```

Check transforms:

```bash
ros2 run tf2_ros tf2_echo map base_link
ros2 run tf2_ros tf2_echo world UF_ROBOT/link6/cameradepth
```

Check Nav2 initial pose:

```bash
ros2 topic echo /initialpose --once
```

Stop a stuck Gazebo GUI/server before relaunching:

```bash
pkill -f "gz sim"
```

## Files Students Usually Touch

- `src/robotino_webots/launch/robotino_gz_xarm_rc2025.launch.py`: main RC2025 xArm test wrapper.
- `src/robotino_webots/launch/robotino_gz_full.launch.py`: Gazebo/Nav2/vision/YOLO full launch.
- `src/ros2-robotino/rto_description/worlds/robotino_gz_rc2025_xarm.sdf`: RC2025 world and table objects.
- `src/vision/vision/yolo_service_node.py`: YOLO service implementation.
- `src/vision/vision/vision_node.py`: interactive vision node and YOLO test trigger.
- `src/robotino_bts/robotino_bts`: behavior tree package.

