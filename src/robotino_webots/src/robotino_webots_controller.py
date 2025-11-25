#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
from tf2_ros import TransformBroadcaster
from geometry_msgs.msg import TransformStamped
import math
from controller import Robot, GPS, Compass

class RobotinoWebotsController(Node):
    def __init__(self):
        super().__init__('robotino_controller')

        self.sub = self.create_subscription(Twist, '/cmd_vel', self.cmd_vel_callback, 10)
        self.odom_pub = self.create_publisher(Odometry, '/odom', 50)
        self.scan_pub = self.create_publisher(LaserScan, '/scan', 50)
        self.tf = TransformBroadcaster(self)

        self.robot = Robot()
        self.dt = int(self.robot.getBasicTimeStep())
        
        # Wheels
        self.wheels = [self.robot.getDevice(f'wheel{i}_joint') for i in range(3)]
        for w in self.wheels:
            w.setPosition(float('inf'))
            w.setVelocity(0.0)

        # Encoders
        self.encoders = [self.robot.getDevice(f'wheel{i}_joint_sensor') for i in range(3)]
        for e in self.encoders:
            e.enable(self.dt)

        # Lidar
        self.lidar = self.robot.getDevice('Hokuyo URG-04LX-UG01')
        self.lidar.enable(self.dt)

        # === GROUND TRUTH SENSORS INITIALIZATION ===
        self.gps = self.robot.getDevice('gps') if self.robot.getDevice('gps') else None
        self.compass = self.robot.getDevice('compass') if self.robot.getDevice('compass') else None
        if self.gps and self.compass:
            self.gps.enable(self.dt)
            self.compass.enable(self.dt)
            self.get_logger().info("GPS and compass enabled for ground truth data.")
        else:
            self.get_logger().warning("Ground truth sensors (GPS/Compass) not found!")
        # =============================================================

        # Kinematics
        self.R = 0.063
        self.L = 0.1826

        # State (Odom variables are now just placeholders, actual Odom logic is commented out)
        self.x = self.y = self.th = 0.0 
        self.last_wheel_pos = [0.0]*3
        self.first = True

        # Command
        self.vx = self.vy = self.w = 0.0

        # Logging
        self.log_cnt = 0

        self.get_logger().info("Robotino controller ready. Only ground truth logs active.")

    def cmd_vel_callback(self, msg):
        self.vx = msg.linear.x
        self.vy = msg.linear.y
        self.w  = msg.angular.z
        self.get_logger().info(f"RECEIVED CMD_VEL: vx={self.vx:.3f}, vy={self.vy:.3f}, w={self.w:.3f}")
    
    
    def step(self):
        while rclpy.ok() and self.robot.step(self.dt) != -1:
            stamp = self.get_clock().now().to_msg()

            # === GET WEBOTS GROUND TRUTH FROM GPS/COMPASS (Corrected Indexing) ===
            if self.gps and self.compass:
                position = self.gps.getValues()
                webots_x = position[0] 
                webots_y = position[2] # Corrected: using Z as Y ground plane
                compass_values = self.compass.getValues()
                webots_yaw_webots_frame = math.atan2(compass_values[0], compass_values[1])
                webots_yaw = math.pi/2 - webots_yaw_webots_frame
                webots_yaw = math.atan2(math.sin(webots_yaw), math.cos(webots_yaw))
            else:
                webots_x, webots_y, webots_yaw = 0.0, 0.0, 0.0
                
            WHEEL_RADIUS = self.R
            DISTANCE_WHEEL_TO_ROBOT_CENTRE = self.L
            
            vx_cmd = self.vx
            vy_cmd = self.vy
            omega_cmd = self.w

            # Correct formula derivation ensures pure vx results in straight line
            w0_target = (-vx_cmd * math.sin(0)      + vy_cmd * math.cos(0)      - DISTANCE_WHEEL_TO_ROBOT_CENTRE * omega_cmd) / WHEEL_RADIUS
            w1_target = (-vx_cmd * math.sin(2.094)  + vy_cmd * math.cos(2.094)  - DISTANCE_WHEEL_TO_ROBOT_CENTRE * omega_cmd) / WHEEL_RADIUS
            w2_target = (-vx_cmd * math.sin(4.188)  + vy_cmd * math.cos(4.188)  - DISTANCE_WHEEL_TO_ROBOT_CENTRE * omega_cmd) / WHEEL_RADIUS
            
            # Note: 2.094 rad is 120 degrees; 4.188 rad is 240 degrees.

            # --- CORRECTED LINES: Use indexing for each wheel ---
            self.wheels[0].setVelocity(w0_target)
            self.wheels[1].setVelocity(w1_target)
            self.wheels[2].setVelocity(w2_target)

            # === FOCUSED LOGS: Only Ground Truth Pose is displayed ===
            if any(abs(v) > 0.05 for v in (w0_target, w1_target, w2_target)):
                self.log_cnt += 1
                if self.log_cnt >= 15:
                    self.log_cnt = 0
                    self.get_logger().info(
                        f"WHEEL TARGETS: [{w0_target:+.2f}, {w1_target:+.2f}, {w2_target:+.2f}] | "
                        f"GROUND TRUTH POSE: ({webots_x:+.2f}m, {webots_y:+.2f}m, {math.degrees(webots_yaw):+6.1f}°)"
                    )
            
            # === Publish Ground Truth as Odom ===
            odom = Odometry()
            odom.header.stamp = stamp
            odom.header.frame_id = 'odom'
            odom.child_frame_id = 'base_footprint'
            odom.pose.pose.position.x = webots_x
            odom.pose.pose.position.y = webots_y
            odom.pose.pose.orientation.z = math.sin(webots_yaw/2)
            odom.pose.pose.orientation.w = math.cos(webots_yaw/2)
            self.odom_pub.publish(odom)

            tf = TransformStamped()
            tf.header.stamp = stamp
            tf.header.frame_id = 'odom'
            tf.child_frame_id = 'base_footprint'
            tf.transform.translation.x = webots_x
            tf.transform.translation.y = webots_y
            tf.transform.rotation.z = math.sin(webots_yaw/2)
            tf.transform.rotation.w = math.cos(webots_yaw/2)
            self.tf.sendTransform(tf)

            ranges = self.lidar.getRangeImage()
            if ranges:
                scan = LaserScan()
                scan.header.stamp = stamp
                scan.header.frame_id = 'laser_frame'
                scan.angle_min = -2.094
                scan.angle_max = 2.094
                scan.angle_increment = 4.188 / 666
                scan.range_min = 0.02
                scan.range_max = 5.6
                scan.ranges = list(reversed(ranges[:666]))
                self.scan_pub.publish(scan)

            rclpy.spin_once(self, timeout_sec=0)

def main():
    rclpy.init()
    node = RobotinoWebotsController()
    node.step()

if __name__ == '__main__':
    main()
