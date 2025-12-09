#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan, JointState, Image
from tf2_ros import TransformBroadcaster
from geometry_msgs.msg import TransformStamped
from builtin_interfaces.msg import Time
import math
import numpy as np
from controller import Robot
from rclpy.parameter import Parameter

# === CAMERA / CV BRIDGE SUPPORT ===
try:
    from cv_bridge import CvBridge
except ImportError:
    CvBridge = None


class RobotinoWebotsController(Node):
    def __init__(self):
        super().__init__('robotino_webots_controller')
        self.set_parameters([
            Parameter('use_sim_time', Parameter.Type.BOOL, False)
        ])

        # --- ROS interfaces ---
        self.subscription = self.create_subscription(Twist, 'cmd_vel', self.cmd_vel_callback, 10)
        self.odom_publisher = self.create_publisher(Odometry, 'odom', 50)
        self.laser_publisher = self.create_publisher(LaserScan, 'scan', 50)
        self.joint_publisher = self.create_publisher(JointState, 'joint_states', 10)
        self.tf_broadcaster = TransformBroadcaster(self)

        # --- Webots robot & basic config ---
        self.robot = Robot()
        self.timestep = 25  # ms

        # Wheels and encoders
        self.wheels = []
        self.wheel_encoders = []
        self.last_wheel_positions = [0.0, 0.0, 0.0]

        for i in range(3):
            wheel = self.robot.getDevice(f'wheel{i}_joint')
            wheel.setPosition(float('inf'))
            self.wheels.append(wheel)

            encoder = self.robot.getDevice(f'wheel{i}_joint_sensor')
            encoder.enable(self.timestep)
            self.wheel_encoders.append(encoder)

        self.WHEEL_RADIUS = 0.038
        self.DISTANCE_WHEEL_TO_ROBOT_CENTRE = 0.1826
        self.base_apply_speeds(0.0, 0.0, 0.0)

        # Lidar
        self.lidar = self.robot.getDevice('Hokuyo URG-04LX-UG01')
        self.lidar.enable(self.timestep)

        # === BRIDGE (single check) ===
        if CvBridge is None:
            self.get_logger().warn('cv_bridge not available, RGB and depth images will NOT be published.')
            self.bridge = None
        else:
            self.bridge = CvBridge()

        # === MAIN FORWARD CAMERA ===
        self.camera = None
        self.camera_publisher = None

        try:
            self.camera = self.robot.getDevice('camera')
            self.camera.enable(self.timestep)
            if self.bridge is not None:
                self.camera_publisher = self.create_publisher(Image, 'camera/image_raw', 10)
                self.get_logger().info('Camera initialized, publishing on camera/image_raw')
        except Exception as e:
            self.get_logger().warn(f'Camera device not found: {e}')
            self.camera = None

        # === KINECT-LIKE RGB-D SENSOR ON PLATFORM ===
        self.kinect_rgb = None
        self.kinect_depth = None
        self.kinect_rgb_pub = None
        self.kinect_depth_pub = None

        try:
            self.kinect_rgb = self.robot.getDevice('kinect_rgb')
            self.kinect_rgb.enable(self.timestep)
            if self.bridge is not None:
                self.kinect_rgb_pub = self.create_publisher(Image, 'kinect/rgb/image_raw', 10)
            self.get_logger().info('Kinect RGB device initialized')
        except Exception as e:
            self.get_logger().warn(f'Kinect RGB device not found: {e}')
            self.kinect_rgb = None

        try:
            self.kinect_depth = self.robot.getDevice('kinect_depth')
            self.kinect_depth.enable(self.timestep)
            if self.bridge is not None:
                self.kinect_depth_pub = self.create_publisher(Image, 'kinect/depth/image_raw', 10)
            self.get_logger().info('Kinect depth device initialized')
        except Exception as e:
            self.get_logger().warn(f'Kinect depth device not found: {e}')
            self.kinect_depth = None

        # Laser scan constants
        self.scan_angle = 240.0 * np.pi / 180.0
        self.angle_increment = self.scan_angle / 666

        # Odometry state
        self.x = 0.0
        self.y = 0.0
        self.th = 0.0
        # last_time in *Webots* time (float seconds)
        self.last_time = float(self.robot.getTime())

        self.get_logger().info(f'Controller initialized: {self.timestep}ms timestep = {1000/self.timestep}Hz')

    def base_apply_speeds(self, vx, vy, omega):
        vx /= self.WHEEL_RADIUS
        vy /= self.WHEEL_RADIUS
        omega *= self.DISTANCE_WHEEL_TO_ROBOT_CENTRE / self.WHEEL_RADIUS
        self.wheels[0].setVelocity(vy - omega)
        self.wheels[1].setVelocity(-math.sqrt(0.75) * vx - 0.5 * vy - omega)
        self.wheels[2].setVelocity(math.sqrt(0.75) * vx - 0.5 * vy - omega)

    def update_odometry(self, current_webots_time):
        """Integrate odom using Webots time, but DO NOT use it for ROS headers."""
        if math.isnan(self.x) or math.isnan(self.y) or math.isnan(self.th):
            self.x = 0.0
            self.y = 0.0
            self.th = 0.0

        try:
            wheel_positions = [encoder.getValue() for encoder in self.wheel_encoders]

            if not hasattr(self, 'wheel_encoders_initialized'):
                self.last_wheel_positions = wheel_positions
                self.wheel_encoders_initialized = True
                return

            delta_wheel0 = wheel_positions[0] - self.last_wheel_positions[0]
            delta_wheel1 = wheel_positions[1] - self.last_wheel_positions[1]
            delta_wheel2 = wheel_positions[2] - self.last_wheel_positions[2]

            self.last_wheel_positions = wheel_positions

            delta_x = self.WHEEL_RADIUS * 1.099 * (0.0000 * delta_wheel0 - 0.8660 * delta_wheel1 + 0.8660 * delta_wheel2)
            delta_y = self.WHEEL_RADIUS * 1.099 * (1.0000 * delta_wheel0 - 0.5000 * delta_wheel1 - 0.5000 * delta_wheel2)
            delta_th = self.WHEEL_RADIUS * -1.617 * (delta_wheel0 + delta_wheel1 + delta_wheel2) / (3.0 * self.DISTANCE_WHEEL_TO_ROBOT_CENTRE)

            dt = current_webots_time - self.last_time
            if dt > 0:
                self.x += delta_x * math.cos(self.th) - delta_y * math.sin(self.th)
                self.y += delta_x * math.sin(self.th) + delta_y * math.cos(self.th)
                self.th += delta_th
                self.th = math.atan2(math.sin(self.th), math.cos(self.th))

            self.last_time = current_webots_time

        except Exception as e:
            self.get_logger().warn(f'Odometry update error: {e}')

    def cmd_vel_callback(self, msg):
        self.base_apply_speeds(msg.linear.x, msg.linear.y, msg.angular.z)

    def get_sim_time(self):
        webots_time = self.robot.getTime()
        stamp = Time()
        stamp.sec = int(webots_time)
        stamp.nanosec = int((webots_time - stamp.sec) * 1e9)
        return stamp

    def run(self):
        self.last_wheel_positions = [encoder.getValue() for encoder in self.wheel_encoders]
        self.wheel_encoders_initialized = True

        self.x = 0.0
        self.y = 0.0
        self.th = 0.0
        self.last_time = float(self.robot.getTime())

        publish_count = 0

        while rclpy.ok() and self.robot.step(self.timestep) != -1:
            rclpy.spin_once(self, timeout_sec=0)

            # Wall-clock ROS time for ALL message headers
            current_ros_time = self.get_clock().now().to_msg()

            # Webots time ONLY for odom integration
            current_webots_time_float = float(self.robot.getTime())

            # Update odometry from wheel encoders (in Webots time)
            self.update_odometry(current_webots_time_float)

            # PUBLISH LASER SCAN with ROS time
            ranges = self.lidar.getRangeImage()
            if ranges:
                laser_scan = LaserScan()
                laser_scan.header.stamp = current_ros_time
                laser_scan.header.frame_id = 'laser_frame'
                laser_scan.angle_min = -self.scan_angle / 2
                laser_scan.angle_max = self.scan_angle / 2
                laser_scan.angle_increment = self.angle_increment
                laser_scan.range_min = 0.05
                laser_scan.range_max = 10.0
                laser_scan.scan_time = self.timestep / 1000.0
                laser_scan.time_increment = 0.0
                laser_scan.ranges = list(reversed(ranges))
                self.laser_publisher.publish(laser_scan)

                if publish_count < 3:
                    self.get_logger().info(f'Laser published: {len(ranges)} ranges')
                    publish_count += 1

            # === MAIN CAMERA PUBLISHING ===
            if self.camera is not None and self.camera_publisher is not None and self.bridge is not None:
                img = self.camera.getImage()
                if img:
                    width = self.camera.getWidth()
                    height = self.camera.getHeight()
                    array = np.frombuffer(img, dtype=np.uint8).reshape((height, width, 4))
                    bgr = array[:, :, :3]

                    image_msg = self.bridge.cv2_to_imgmsg(bgr, encoding='bgr8')
                    image_msg.header.stamp = current_ros_time
                    image_msg.header.frame_id = 'camera_link'
                    self.camera_publisher.publish(image_msg)

            # === KINECT RGB PUBLISHING ===
            if self.kinect_rgb is not None and self.kinect_rgb_pub is not None and self.bridge is not None:
                k_img = self.kinect_rgb.getImage()
                if k_img:
                    kw = self.kinect_rgb.getWidth()
                    kh = self.kinect_rgb.getHeight()
                    k_array = np.frombuffer(k_img, dtype=np.uint8).reshape((kh, kw, 4))
                    k_bgr = k_array[:, :, :3]
                    k_msg = self.bridge.cv2_to_imgmsg(k_bgr, encoding='bgr8')
                    k_msg.header.stamp = current_ros_time
                    k_msg.header.frame_id = 'kinect_link'
                    self.kinect_rgb_pub.publish(k_msg)

            # === KINECT DEPTH PUBLISHING (32FC1) ===
            if self.kinect_depth is not None and self.kinect_depth_pub is not None and self.bridge is not None:
                depth_buffer = self.kinect_depth.getRangeImage()
                if depth_buffer:
                    dw = self.kinect_depth.getWidth()
                    dh = self.kinect_depth.getHeight()
                    depth_array = np.array(depth_buffer, dtype=np.float32).reshape((dh, dw))
                    depth_msg = self.bridge.cv2_to_imgmsg(depth_array, encoding='32FC1')
                    depth_msg.header.stamp = current_ros_time
                    depth_msg.header.frame_id = 'kinect_link'
                    self.kinect_depth_pub.publish(depth_msg)

            # PUBLISH ODOMETRY with ROS time
            odom_msg = Odometry()
            odom_msg.header.stamp = current_ros_time
            odom_msg.header.frame_id = 'odom'
            odom_msg.child_frame_id = 'base_footprint'

            odom_msg.pose.pose.position.x = self.x
            odom_msg.pose.pose.position.y = self.y
            odom_msg.pose.pose.position.z = 0.0

            odom_msg.pose.pose.orientation.x = 0.0
            odom_msg.pose.pose.orientation.y = 0.0
            odom_msg.pose.pose.orientation.z = math.sin(self.th / 2.0)
            odom_msg.pose.pose.orientation.w = math.cos(self.th / 2.0)

            self.odom_publisher.publish(odom_msg)

            # TF TRANSFORMS
            # odom -> base_footprint
            t1 = TransformStamped()
            t1.header.stamp = current_ros_time
            t1.header.frame_id = 'odom'
            t1.child_frame_id = 'base_footprint'
            t1.transform.translation.x = self.x
            t1.transform.translation.y = self.y
            t1.transform.translation.z = 0.0
            t1.transform.rotation.x = 0.0
            t1.transform.rotation.y = 0.0
            t1.transform.rotation.z = math.sin(self.th / 2.0)
            t1.transform.rotation.w = math.cos(self.th / 2.0)
            self.tf_broadcaster.sendTransform(t1)

            # base_footprint -> laser_frame
            t2 = TransformStamped()
            t2.header.stamp = current_ros_time
            t2.header.frame_id = 'base_footprint'
            t2.child_frame_id = 'laser_frame'
            t2.transform.translation.x = 0.0
            t2.transform.translation.y = 0.0
            t2.transform.translation.z = 0.2
            t2.transform.rotation.x = 0.0
            t2.transform.rotation.y = 0.0
            t2.transform.rotation.z = 0.0
            t2.transform.rotation.w = 1.0
            self.tf_broadcaster.sendTransform(t2)

            # === CAMERA TF (rough pose, can be tuned later) ===
            if self.camera is not None:
                t3 = TransformStamped()
                t3.header.stamp = current_ros_time
                t3.header.frame_id = 'base_footprint'
                t3.child_frame_id = 'camera_link'
                t3.transform.translation.x = 0.1   # approx in front of robot
                t3.transform.translation.y = 0.0
                t3.transform.translation.z = 0.25  # approx height
                t3.transform.rotation.x = 0.0
                t3.transform.rotation.y = 0.0
                t3.transform.rotation.z = 0.0
                t3.transform.rotation.w = 1.0
                self.tf_broadcaster.sendTransform(t3)

            # === KINECT TF (on the platform) ===
            if self.kinect_rgb is not None or self.kinect_depth is not None:
                t4 = TransformStamped()
                t4.header.stamp = current_ros_time
                t4.header.frame_id = 'base_footprint'
                t4.child_frame_id = 'kinect_link'
                t4.transform.translation.x = 0.0
                t4.transform.translation.y = 0.0
                t4.transform.translation.z = 0.60   # should match Webots translation
                t4.transform.rotation.x = 0.0
                t4.transform.rotation.y = 0.0
                t4.transform.rotation.z = 0.0
                t4.transform.rotation.w = 1.0
                self.tf_broadcaster.sendTransform(t4)

            # JOINT STATES (for RViz wheels)
            joint_msg = JointState()
            joint_msg.header.stamp = current_ros_time
            joint_msg.name = ['wheel0_joint', 'wheel1_joint', 'wheel2_joint']
            wheel_positions = [encoder.getValue() for encoder in self.wheel_encoders]
            joint_msg.position = wheel_positions
            self.joint_publisher.publish(joint_msg)


def main(args=None):
    rclpy.init(args=args)
    controller = RobotinoWebotsController()
    try:
        controller.run()
    finally:
        controller.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
