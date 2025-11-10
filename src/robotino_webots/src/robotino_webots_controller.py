#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan
import math
import numpy as np
from controller import Robot

class RobotinoWebotsController(Node):
    def __init__(self):
        super().__init__('robotino_webots_controller')
        
        # Subscribe to cmd_vel
        self.subscription = self.create_subscription(
            Twist,
            'cmd_vel',
            self.cmd_vel_callback,
            10)
        self.subscription  # prevent unused variable warning
        
        # Publish odometry
        self.odom_publisher = self.create_publisher(Odometry, 'odom', 10)
        
        # Webots robot instance
        self.robot = Robot()
        self.timestep = int(self.robot.getBasicTimeStep())
        
        # Get wheels (using our proven code)
        self.wheels = []
        for i in range(3):
            wheel = self.robot.getDevice(f'wheel{i}_joint')
            wheel.setPosition(float('inf'))
            self.wheels.append(wheel)
            
        # Webots constants (from base.c)
        self.WHEEL_RADIUS = 0.063
        self.DISTANCE_WHEEL_TO_ROBOT_CENTRE = 0.1826
        
        # Start with zero velocity
        self.base_apply_speeds(0.0, 0.0, 0.0)
        
        # Get lidar device with the correct name
        self.lidar = self.robot.getDevice('Hokuyo URG-04LX-UG01')
        self.lidar.enable(self.timestep)
        self.lidar.enablePointCloud()
        
        # Create laser scan publisher
        self.laser_publisher = self.create_publisher(LaserScan, 'scan', 10)
        
        # Laser scan parameters
        self.laser_scan = LaserScan()
        self.laser_scan.header.frame_id = 'laser_frame'
        self.laser_scan.angle_min = -np.pi
        self.laser_scan.angle_max = np.pi
        self.laser_scan.angle_increment = 2 * np.pi / 682
        self.laser_scan.range_min = 0.05
        self.laser_scan.range_max = 4.0
        self.laser_scan.time_increment = 0.0
        self.laser_scan.scan_time = 0.1
        
        self.get_logger().info('Robotino Webots ROS2 Controller Started with Lidar!')
    
    def base_apply_speeds(self, vx, vy, omega):
        """EXACT SAME FUNCTION WE PROVED WORKS - now with ROS2!"""
        vx /= self.WHEEL_RADIUS
        vy /= self.WHEEL_RADIUS  
        omega *= self.DISTANCE_WHEEL_TO_ROBOT_CENTRE / self.WHEEL_RADIUS
        
        self.wheels[0].setVelocity(vy - omega)
        self.wheels[1].setVelocity(-math.sqrt(0.75) * vx - 0.5 * vy - omega)
        self.wheels[2].setVelocity(math.sqrt(0.75) * vx - 0.5 * vy - omega)
    
    def cmd_vel_callback(self, msg):
        """Map ROS2 Twist to our proven wheel control"""
        self.get_logger().info(f'Received cmd_vel: vx={msg.linear.x:.2f}, vy={msg.linear.y:.2f}, omega={msg.angular.z:.2f}')
        
        # Map ROS2 Twist to our proven control
        self.base_apply_speeds(msg.linear.x, msg.linear.y, msg.angular.z)
    
    def run(self):
        """Main control loop"""
        while rclpy.ok() and self.robot.step(self.timestep) != -1:
            rclpy.spin_once(self, timeout_sec=0)
            
            # Publish laser scan
            ranges = self.lidar.getRangeImage()
            if ranges:
                self.laser_scan.ranges = ranges
                self.laser_scan.header.stamp = self.get_clock().now().to_msg()
                self.laser_publisher.publish(self.laser_scan)

def main(args=None):
    rclpy.init(args=args)
    controller = RobotinoWebotsController()
    
    try:
        controller.run()
    except KeyboardInterrupt:
        pass
    finally:
        controller.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()
