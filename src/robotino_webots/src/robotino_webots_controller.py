#!/usr/bin/env python3
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Twist
from nav_msgs.msg import Odometry
from sensor_msgs.msg import LaserScan, JointState
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
        self.joint_publisher = self.create_publisher(JointState, 'joint_states', 10)
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
            
        #self.WHEEL_RADIUS = 0.063
        self.WHEEL_RADIUS = 0.0315  # Half the value
        self.DISTANCE_WHEEL_TO_ROBOT_CENTRE = 0.1826
        self.base_apply_speeds(0.0, 0.0, 0.0)
        
        # Lidar
        self.lidar = self.robot.getDevice('Hokuyo URG-04LX-UG01')
        self.lidar.enable(self.timestep)
        
        # Laser scan
        self.laser_scan = LaserScan()
        self.laser_scan.header.frame_id = 'laser_frame'
                
        scan_angle = 240.0 * np.pi / 180.0
        self.laser_scan.angle_min = -scan_angle / 2
        self.laser_scan.angle_max = scan_angle / 2
        self.laser_scan.angle_increment = scan_angle / 666
        self.laser_scan.range_min = 0.05
        self.laser_scan.range_max = 10.0
        self.laser_scan.scan_time = 0.1
        
        # Odometry state
        self.x = 0.0
        self.y = 0.0
        self.th = 0.0
        self.last_time = float(self.robot.getTime())
        
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
            
            delta_x = self.WHEEL_RADIUS * 0.83 * (0.0000 * delta_wheel0 - 0.8660 * delta_wheel1 + 0.8660 * delta_wheel2)
            delta_y = self.WHEEL_RADIUS * 0.83 * (1.0000 * delta_wheel0 - 0.5000 * delta_wheel1 - 0.5000 * delta_wheel2)
            #delta_th = self.WHEEL_RADIUS * (-0.3849 * delta_wheel0 - 0.3849 * delta_wheel1 - 0.3849 * delta_wheel2) / self.DISTANCE_WHEEL_TO_ROBOT_CENTRE
            delta_th = self.WHEEL_RADIUS * -2 * (delta_wheel0 + delta_wheel1 + delta_wheel2) / (3.0 * self.DISTANCE_WHEEL_TO_ROBOT_CENTRE)
            print(f"Resulting motion: dx={delta_x:.6f}, dy={delta_y:.6f}, dth={delta_th:.6f}")
            
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
    
    def get_sim_time(self):
        webots_time = float(self.robot.getTime())
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
            
            current_sim_time = self.get_sim_time()
            current_webots_time_float = float(self.robot.getTime())
            
            # Update odometry from wheel encoders
            self.update_odometry(current_webots_time_float)
            
            # PUBLISH LASER SCAN EVERY TIMESTEP (removed throttling)
            ranges = self.lidar.getRangeImage()
            

            #ranges = self.lidar.getRangeImage()
            if ranges:
                # ADD DEBUG HERE:
                if len(ranges) > 10:
                    left_wall_dist = ranges[0]    # Should be left side
                    right_wall_dist = ranges[-1]  # Should be right side  
                    front_wall_dist = ranges[len(ranges)//2]  # Should be front
                    print(f"ANGLE RANGE: {self.laser_scan.angle_min:.3f} to {self.laser_scan.angle_max:.3f} rad")
                    print(f"ANGLE RANGE: {np.degrees(self.laser_scan.angle_min):.1f} to {np.degrees(self.laser_scan.angle_max):.1f} deg")
                    print(f"Webots Laser: Left={left_wall_dist:.2f}, Front={front_wall_dist:.2f}, Right={right_wall_dist:.2f}")
            
                #self.laser_scan.ranges = ranges
                self.laser_scan.ranges = list(reversed(ranges))
                self.laser_scan.header.stamp = current_sim_time
                self.laser_publisher.publish(self.laser_scan)
            
            # PUBLISH ODOMETRY, TF, AND JOINT STATES EVERY TIMESTEP (removed throttling)
            # ODOMETRY
            odom_msg = Odometry()
            odom_msg.header.stamp = current_sim_time
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
            t1 = TransformStamped()
            t1.header.stamp = current_sim_time
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
            t2.header.stamp = current_sim_time
            t2.header.frame_id = 'base_footprint'
            t2.child_frame_id = 'laser_frame'
            t2.transform.translation.z = 0.2
            t2.transform.rotation.w = 1.0
            self.tf_broadcaster.sendTransform(t2)
            
            # JOINT STATES
            joint_msg = JointState()
            joint_msg.header.stamp = current_sim_time
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