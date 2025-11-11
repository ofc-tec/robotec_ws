#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
from tf2_ros import TransformBroadcaster
from geometry_msgs.msg import TransformStamped
from builtin_interfaces.msg import Time
import math
import numpy as np
from controller import Robot

class RobotinoWebotsController(Node):
    def __init__(self):
        super().__init__('robotino_webots_controller')
        
        self.subscription = self.create_subscription(Twist, 'cmd_vel', self.cmd_vel_callback, 10)
        self.odom_publisher = self.create_publisher(Odometry, 'odom', 10)
        self.laser_publisher = self.create_publisher(LaserScan, 'scan', 10)
        self.tf_broadcaster = TransformBroadcaster(self)
        
        self.robot = Robot()
        self.timestep = int(self.robot.getBasicTimeStep())
        
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
            
        self.WHEEL_RADIUS = 0.063
        self.DISTANCE_WHEEL_TO_ROBOT_CENTRE = 0.1826
        self.base_apply_speeds(0.0, 0.0, 0.0)
        
        # Lidar
        self.lidar = self.robot.getDevice('Hokuyo URG-04LX-UG01')
        self.lidar.enable(self.timestep)
        
        # Laser scan - use 'laser_frame' to match what SLAM sees
        self.laser_scan = LaserScan()
        self.laser_scan.header.frame_id = 'laser_frame'
        
        # Hokuyo URG-04LX: 240 degrees field of view
        scan_angle = 240.0 * np.pi / 180.0  # Correct 240° FOV
        self.laser_scan.angle_min = -scan_angle / 2
        self.laser_scan.angle_max = scan_angle / 2
        self.laser_scan.angle_increment = scan_angle / 666  # 667 points = 666 increments
        self.laser_scan.range_min = 0.05
        self.laser_scan.range_max = 4.0
        self.laser_scan.scan_time = 0.1
        
        # Odometry state
        self.x = 0.0
        self.y = 0.0
        self.th = 0.0
        self.last_time = float(self.robot.getTime())
        
        # Throttling
        self.last_scan_time = 0
        self.last_tf_time = 0
        self.publish_rate = 0.1
        
        self.get_logger().info('SLAM READY - ODOMETRY ACTIVE')
    
    def base_apply_speeds(self, vx, vy, omega):
        vx /= self.WHEEL_RADIUS
        vy /= self.WHEEL_RADIUS  
        omega *= self.DISTANCE_WHEEL_TO_ROBOT_CENTRE / self.WHEEL_RADIUS
        self.wheels[0].setVelocity(vy - omega)
        self.wheels[1].setVelocity(-math.sqrt(0.75) * vx - 0.5 * vy - omega)
        self.wheels[2].setVelocity(math.sqrt(0.75) * vx - 0.5 * vy - omega)
    
    def update_odometry(self, current_time):
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
            
            delta_x = self.WHEEL_RADIUS * (0.0000 * delta_wheel0 - 0.8660 * delta_wheel1 + 0.8660 * delta_wheel2)
            delta_y = self.WHEEL_RADIUS * (1.0000 * delta_wheel0 - 0.5000 * delta_wheel1 - 0.5000 * delta_wheel2)
            delta_th = self.WHEEL_RADIUS * (-0.3849 * delta_wheel0 - 0.3849 * delta_wheel1 - 0.3849 * delta_wheel2) / self.DISTANCE_WHEEL_TO_ROBOT_CENTRE
            
            dt = current_time - self.last_time
            if dt > 0:
                self.x += delta_x * math.cos(self.th) - delta_y * math.sin(self.th)
                self.y += delta_x * math.sin(self.th) + delta_y * math.cos(self.th)
                self.th += delta_th
                self.th = math.atan2(math.sin(self.th), math.cos(self.th))
            
            self.last_time = current_time
            
        except Exception as e:
            pass

    def cmd_vel_callback(self, msg):
        self.base_apply_speeds(msg.linear.x, msg.linear.y, msg.angular.z)
    
    def webots_time_to_ros_time(self, webots_time):
        """Convert Webots simulation time to proper ROS 2 Time message"""
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
        
        while rclpy.ok() and self.robot.step(self.timestep) != -1:
            rclpy.spin_once(self, timeout_sec=0)
            
            current_time = self.robot.getTime()
            
            # Update odometry from wheel encoders
            self.update_odometry(current_time)
            
            # Laser scan at 10Hz - PROPER SIMULATION TIME
            if current_time - self.last_scan_time > self.publish_rate:
                ranges = self.lidar.getRangeImage()
                if ranges:
                    self.laser_scan.ranges = ranges
                    # FIXED: Use proper simulation time
                    self.laser_scan.header.stamp = self.webots_time_to_ros_time(current_time)
                    self.laser_publisher.publish(self.laser_scan)
                    self.last_scan_time = current_time
            
            # TF and ODOMETRY at 10Hz - PROPER SIMULATION TIME
            if current_time - self.last_tf_time > self.publish_rate:
                current_ros_time = self.webots_time_to_ros_time(current_time)
                
                # ODOMETRY PUBLISHING
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
                
                # TF transforms
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
                
                t2 = TransformStamped()
                t2.header.stamp = current_ros_time
                t2.header.frame_id = 'base_footprint'
                t2.child_frame_id = 'laser_frame'
                t2.transform.translation.z = 0.2
                t2.transform.rotation.w = 1.0
                self.tf_broadcaster.sendTransform(t2)
                
                self.last_tf_time = current_time

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