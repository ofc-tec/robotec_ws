# 🤖 Robotec – ROS 2 Jazzy + Gazebo Sim 8 (Harmonic)

Fully working simulation of **Robotec**, a differential-drive robot integrated with **Gazebo Sim 8** and **ROS 2 Jazzy**.

✅ `/scan` from GPU LiDAR  
✅ `/odom` from DiffDrive plugin  
✅ `/cmd_vel` control through ROS 2 bridge  
✅ `/clock` synchronization  
✅ Confirmed working on **Ubuntu 22.04**

---

## 🧩 Workspace Structure

```
robotino_ros2_ws/
├── src/ros2-robotino/rto_description/   # meshes, URDF/XACROs
├── models/robotec.sdf                   # model with LiDAR + DiffDrive
├── worlds/lidar_ok.sdf                  # world including Robotec
├── build/ install/ log/                 # auto-generated (ignored)
└── README.md
```

---

## ⚙️ Installation & Setup

### 1️⃣ Install ROS 2 Jazzy and Gazebo Sim 8
```bash
sudo apt update
sudo apt install ros-jazzy-desktop-full
sudo apt install ros-jazzy-ros-gz-sim ros-jazzy-ros-gz-bridge                  ros-jazzy-ros-gz-interfaces ros-jazzy-ros-gz-msgs
sudo apt install libgz-sim8-plugins  # adds Factory, DiffDrive, GPU-Lidar
```

---

### 2️⃣ Build with Symlinks
```bash
cd ~/robotino_ros2_ws
colcon build --symlink-install
source install/setup.bash
```

To persist:
```bash
echo "source ~/robotino_ros2_ws/install/setup.bash" >> ~/.bashrc
```

---

### 3️⃣ Export Gazebo Resources
```bash
export GZ_SIM_RESOURCE_PATH=$GZ_SIM_RESOURCE_PATH:\
$HOME/robotino_ros2_ws/src/ros2-robotino/rto_description:\
$HOME/robotino_ros2_ws/models
```

Add that line to `~/.bashrc` to make it permanent.

---

## 🚀 Run the Simulation

### Launch Gazebo World
```bash
gz sim -r worlds/lidar_ok.sdf
```

### Verify Topics (Gazebo side)
```bash
gz topic --list
gz topic --echo --topic /scan
gz topic --echo --topic /odom
```

---

## 🔗 Bridge Gazebo ↔ ROS 2

```bash
ros2 run ros_gz_bridge parameter_bridge \
  "/scan@sensor_msgs/msg/LaserScan[gz.msgs.LaserScan" \
  "/odom@nav_msgs/msg/Odometry[gz.msgs.Odometry" \
  "/cmd_vel@geometry_msgs/msg/Twist]gz.msgs.Twist" \
  "/clock@rosgraph_msgs/msg/Clock[gz.msgs.Clock"
```

Check:
```bash
ros2 topic list
ros2 topic echo /scan --once
ros2 topic echo /odom --once
```

---

## 🕹️ Drive the Robot

```bash
ros2 topic pub /cmd_vel geometry_msgs/Twist \
  '{linear: {x: 0.2}, angular: {z: 0.0}}' -r 2
```

You should see `/odom` updating and `/scan` producing data.

---

## 🧱 Main Components

| Component | File | Function |
|------------|------|-----------|
| **World** | `worlds/lidar_ok.sdf` | Includes Robotec, sensors, lighting |
| **Model** | `models/robotec.sdf` | Defines base, LiDAR, DiffDrive |
| **Plugin** | `libgz-sim8-gpu-lidar-system.so` | Publishes `/scan` |
| **Plugin** | `libgz-sim8-diff-drive-system.so` | Publishes `/odom`, reads `/cmd_vel` |
| **Bridge** | `ros_gz_bridge` | Syncs Gazebo topics to ROS 2 |

---

## 🧭 Next Steps

1. **Install SLAM Toolbox**
   ```bash
   sudo apt install ros-jazzy-slam-toolbox
   ```
2. **Run RViz** and visualize `/map`, `/scan`, `/odom`.
3. **Integrate Nav2** later:
   ```bash
   sudo apt install ros-jazzy-nav2-bringup
   ```

---

## 🧹 .gitignore
```
build/
install/
log/
__pycache__/
*.pyc
```

---

## 👷‍♂️ Maintainer

**Dr. Oscar Francisco Fuentes Casarrubias**  
UNAM Biorobotics Lab | Tec de Monterrey  
_This snapshot documents the working November 2025 ROS 2 Jazzy + GZ Sim 8 setup._
