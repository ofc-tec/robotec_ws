#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image, PointCloud2
from cv_bridge import CvBridge, CvBridgeError


class VisionNode(Node):
    def __init__(self) -> None:
        super().__init__('vision_node')

        # --- Parameters ---
        # Topic for incoming RGB image
        self.declare_parameter('image_topic', '/camera/image_raw')
        # Optional topic for future point cloud subscriber
        self.declare_parameter('pointcloud_topic', '')

        image_topic = self.get_parameter('image_topic').get_parameter_value().string_value
        pointcloud_topic = self.get_parameter('pointcloud_topic').get_parameter_value().string_value

        self.get_logger().info(f'[vision] Using image_topic: {image_topic}')
        if pointcloud_topic:
            self.get_logger().info(f'[vision] PointCloud placeholder topic: {pointcloud_topic}')
        else:
            self.get_logger().info('[vision] PointCloud subscriber is disabled (empty topic).')

        # --- CvBridge for image conversions ---
        self.bridge = CvBridge()

        # --- Subscriptions ---
        # Image subscriber
        self.image_sub = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10
        )

        # Placeholder for PointCloud2 subscriber (no processing yet)
        self.pointcloud_sub = None
        if pointcloud_topic:
            self.pointcloud_sub = self.create_subscription(
                PointCloud2,
                pointcloud_topic,
                self.pointcloud_callback,
                10
            )

    # --------------- Callbacks ----------------
    def image_callback(self, msg: Image) -> None:
        """Main hook to plug in all your old vision code."""
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except CvBridgeError as e:
            self.get_logger().error(f'CvBridge error: {e}')
            return

        # TODO: here is where we’ll start adding all the segmentation / CLIP / YOLO / DINO magic
        h, w = cv_image.shape[:2]
        self.get_logger().debug(f'[vision] Received image {w}x{h}')

        # For now, do nothing else – no imshow, no waitKey, just spin.

    def pointcloud_callback(self, msg: PointCloud2) -> None:
        """Placeholder for future point cloud processing."""
        # TODO: point cloud handling (ros_numpy / open3d / etc.)
        self.get_logger().debug('[vision] Received PointCloud2 message (placeholder).')


def main(args=None) -> None:
    rclpy.init(args=args)
    node = VisionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Shutting down vision_node (Ctrl+C).')
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
