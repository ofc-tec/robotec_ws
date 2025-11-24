#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
from tf2_ros import TransformBroadcaster
from geometry_msgs.msg import TransformStamped
import math
from controller import Robot


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

        # Kinematics
        self.R = 0.063
        self.L = 0.1826

        # State
        self.x = self.y = self.th = 0.0
        self.last_wheel_pos = [0.0]*3
        self.first = True

        # Command — THIS WAS THE ONLY MISSING LINE
        self.vx = self.vy = self.w = 0.0

        # Logging
        self.log_cnt = 0

        self.get_logger().info("Robotino controller — back to the version that actually worked")

    def cmd_vel_callback(self, msg):
        self.vx = msg.linear.x
        self.vy = msg.linear.y
        self.w  = msg.angular.z

    def step(self):
        while rclpy.ok() and self.robot.step(self.dt) != -1:
            stamp = self.get_clock().now().to_msg()

            # === Perfect kinematics ===
            w0 =  self.vy / self.R                              - self.w * self.L / self.R
            w1 = -math.sin(math.pi/3) * self.vx / self.R - 0.5 * self.vy / self.R - self.w * self.L / self.R
            w2 =  math.sin(math.pi/3) * self.vx / self.R - 0.5 * self.vy / self.R - self.w * self.L / self.R

            self.wheels[0].setVelocity(w0)
            self.wheels[1].setVelocity(w1)
            self.wheels[2].setVelocity(w2)

            # === Your logs with orientation ===
            if any(abs(v) > 0.05 for v in (w0, w1, w2)):
                self.log_cnt += 1
                if self.log_cnt >= 15:
                    self.log_cnt = 0
                    self.get_logger().info(
                        f"WHEEL: [{w0:+.2f}, {w1:+.2f}, {w2:+.2f}] | CMD: [{self.vx:+.3f}, {self.vy:+.3f}, {self.w:+.3f}] | θ={math.degrees(self.th):+6.1f}°"
                    )

            # === Perfect wheel encoder odometry ===
            curr = [e.getValue() for e in self.encoders]
            if self.first:
                self.last_wheel_pos = curr
                self.first = False
                continue

            dpos = [c - l for c, l in zip(curr, self.last_wheel_pos)]
            self.last_wheel_pos = curr

            d0 = dpos[0] * self.R
            d1 = dpos[1] * self.R
            d2 = dpos[2] * self.R

            dx = ( -math.sqrt(3)/2 * d1 + math.sqrt(3)/2 * d2 ) / 3.0
            dy = (  d0 - 0.5 * d1 - 0.5 * d2 ) / 3.0
            dth = (d0 + d1 + d2) / (3.0 * self.L)

            self.th += dth
            self.th = math.atan2(math.sin(self.th), math.cos(self.th))
            self.x += dx * math.cos(self.th) - dy * math.sin(self.th)
            self.y += dx * math.sin(self.th) + dy * math.cos(self.th)

            # === Publish everything ===
            odom = Odometry()
            odom.header.stamp = stamp
            odom.header.frame_id = 'odom'
            odom.child_frame_id = 'base_footprint'
            odom.pose.pose.position.x = self.x
            odom.pose.pose.position.y = self.y
            odom.pose.pose.orientation.z = math.sin(self.th/2)
            odom.pose.pose.orientation.w = math.cos(self.th/2)
            self.odom_pub.publish(odom)

            tf = TransformStamped()
            tf.header.stamp = stamp
            tf.header.frame_id = 'odom'
            tf.child_frame_id = 'base_footprint'
            tf.transform.translation.x = self.x
            tf.transform.translation.y = self.y
            tf.transform.rotation.z = math.sin(self.th/2)
            tf.transform.rotation.w = math.cos(self.th/2)
            self.tf.sendTransform(tf)

            tf_laser = TransformStamped()
            tf_laser.header.stamp = stamp
            tf_laser.header.frame_id = 'base_footprint'
            tf_laser.child_frame_id = 'laser_frame'
            tf_laser.transform.translation.z = 0.3728
            tf_laser.transform.rotation.w = 1.0
            self.tf.sendTransform(tf_laser)

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