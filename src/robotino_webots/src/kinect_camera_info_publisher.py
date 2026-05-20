#!/usr/bin/env python3
import math

import rclpy
from rclpy.node import Node
from sensor_msgs.msg import CameraInfo


class KinectCameraInfoPublisher(Node):
    def __init__(self):
        super().__init__('kinect_camera_info_publisher')
        self.declare_parameter('rgb_camera_info_topic', '/kinect_sim/rgb/camera_info')
        self.declare_parameter('depth_camera_info_topic', '/kinect_sim/depth/camera_info')
        self.declare_parameter('frame_id', 'kinect_link')
        self.declare_parameter('width', 640)
        self.declare_parameter('height', 480)
        self.declare_parameter('hfov', 1.047)
        self.declare_parameter('publish_rate', 15.0)

        self.frame_id = self.get_parameter('frame_id').value
        self.width = int(self.get_parameter('width').value)
        self.height = int(self.get_parameter('height').value)
        self.hfov = float(self.get_parameter('hfov').value)

        self.rgb_pub = self.create_publisher(
            CameraInfo,
            self.get_parameter('rgb_camera_info_topic').value,
            10,
        )
        self.depth_pub = self.create_publisher(
            CameraInfo,
            self.get_parameter('depth_camera_info_topic').value,
            10,
        )

        rate = float(self.get_parameter('publish_rate').value)
        self.timer = self.create_timer(1.0 / rate, self.publish_camera_info)
        self.get_logger().info(
            f'Publishing Kinect CameraInfo {self.width}x{self.height} hfov={self.hfov} frame={self.frame_id}'
        )

    def make_msg(self):
        vfov = 2.0 * math.atan(math.tan(self.hfov / 2.0) * (self.height / self.width))
        fx = self.width / (2.0 * math.tan(self.hfov / 2.0))
        fy = self.height / (2.0 * math.tan(vfov / 2.0))
        cx = (self.width - 1) / 2.0
        cy = (self.height - 1) / 2.0

        msg = CameraInfo()
        msg.header.stamp = self.get_clock().now().to_msg()
        msg.header.frame_id = self.frame_id
        msg.width = self.width
        msg.height = self.height
        msg.distortion_model = 'plumb_bob'
        msg.d = [0.0, 0.0, 0.0, 0.0, 0.0]
        msg.k = [
            fx, 0.0, cx,
            0.0, fy, cy,
            0.0, 0.0, 1.0,
        ]
        msg.r = [
            1.0, 0.0, 0.0,
            0.0, 1.0, 0.0,
            0.0, 0.0, 1.0,
        ]
        msg.p = [
            fx, 0.0, cx, 0.0,
            0.0, fy, cy, 0.0,
            0.0, 0.0, 1.0, 0.0,
        ]
        return msg

    def publish_camera_info(self):
        msg = self.make_msg()
        self.rgb_pub.publish(msg)
        self.depth_pub.publish(msg)


def main():
    rclpy.init()
    node = KinectCameraInfoPublisher()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
