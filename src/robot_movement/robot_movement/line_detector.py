#!/usr/bin/env python3

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import LaserScan
from std_msgs.msg import Float32
import math
import numpy as np

class LineDetector(Node):
    def __init__(self):
        super().__init__('line_detector')
        
        # Publishers for both angle and distance
        self.angle_pub = self.create_publisher(Float32, 'line_angle', 10)
        self.distance_pub = self.create_publisher(Float32, 'line_distance', 10) 
        self.scan_sub = self.create_subscription(LaserScan, 'scan', self.scan_callback, 10)
        
        self.get_logger().info('Line detector started - waiting for /scan data...')
    
    def scan_callback(self, msg):
        # Simple front sector: ±30 degrees
        front_start = -math.pi/6
        front_end = math.pi/6
        
        angles = []
        ranges = []
        
        current_angle = msg.angle_min
        for range_val in msg.ranges:
            if front_start <= current_angle <= front_end:
                if not math.isinf(range_val) and msg.range_min <= range_val <= msg.range_max:
                    angles.append(current_angle)
                    ranges.append(range_val)
            current_angle += msg.angle_increment
        
        if len(angles) < 5:
            self.get_logger().warn('Not enough points in front sector')
            return
        
        # Convert to Cartesian and fit line
        x = np.array(ranges) * np.cos(angles)
        y = np.array(ranges) * np.sin(angles)
        
        A = np.vstack([x, np.ones(len(x))]).T
        m, c = np.linalg.lstsq(A, y, rcond=None)[0]
        
        line_angle = math.atan(m)
        
        # Calculate distance to line using point-line distance formula
        # For line: y = mx + c, distance from origin (0,0) is |c| / sqrt(m² + 1)
        distance = abs(c) / math.sqrt(m**2 + 1)
        
        # Publish the angle
        angle_msg = Float32()
        angle_msg.data = line_angle
        self.angle_pub.publish(angle_msg)
        
        # Publish the distance
        distance_msg = Float32()
        distance_msg.data = distance
        self.distance_pub.publish(distance_msg)
        
        self.get_logger().info(f'Line angle: {line_angle:.3f} rad ({math.degrees(line_angle):.1f}°), Distance: {distance:.3f} m')

def main(args=None):
    rclpy.init(args=args)
    node = LineDetector()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()

if __name__ == '__main__':
    main()