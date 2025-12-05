#!/usr/bin/env python3
# -*- coding: utf-8 -*-

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image, PointCloud2
from cv_bridge import CvBridge, CvBridgeError

import cv2


class VisionNode(Node):
    def __init__(self) -> None:
        super().__init__('vision_node')

        # --- Parameters ---
        self.declare_parameter('image_topic', '/camera/image_raw')
        self.declare_parameter('pointcloud_topic', '')

        image_topic = self.get_parameter('image_topic').get_parameter_value().string_value
        pointcloud_topic = self.get_parameter('pointcloud_topic').get_parameter_value().string_value

        self.get_logger().info(f'[vision] Using image_topic: {image_topic}')
        if pointcloud_topic:
            self.get_logger().info(f'[vision] PointCloud subscriber is enabled on: {pointcloud_topic}')
        else:
            self.get_logger().info('[vision] PointCloud subscriber is disabled (empty topic).')

        # CvBridge
        self.bridge = CvBridge()

        # OpenCV window (same spirit as your ROS1 code)
        self.window_name = 'class rgbd'
        cv2.namedWindow(self.window_name, cv2.WINDOW_NORMAL)

        # Subscriptions
        self.image_sub = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10
        )

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
        """Main hook to plug in all your old vision code (segmentation, CLIP, YOLO, etc.)."""
        try:
            cv_image = self.bridge.imgmsg_to_cv2(msg, desired_encoding='bgr8')
        except CvBridgeError as e:
            self.get_logger().error(f'CvBridge error: {e}')
            return

        # HERE is where we’ll later add:
        # - segmentation trackbars
        # - CLIP / YOLO / DINO calls
        # - plane finding, etc.

        # For now: just display the image in the 'class rgbd' window
        cv2.imshow(self.window_name, cv_image)

        # Handle keyboard input (like your ROS1 node):
        key = cv2.waitKey(1) & 0xFF
        if key == ord('q'):
            self.get_logger().info("Key 'q' pressed – closing window and shutting down node.")
            cv2.destroyAllWindows()
            # This will cause rclpy.spin() to return
            rclpy.shutdown()

    def pointcloud_callback(self, msg: PointCloud2) -> None:
        """Placeholder for future point cloud processing."""
        # TODO: When you have a PC2 topic, we can port the RGBD/point cloud logic here.
        self.get_logger().debug('[vision] Received PointCloud2 message (placeholder).')

    def destroy_node(self):
        """Ensure OpenCV windows are closed on shutdown."""
        try:
            cv2.destroyAllWindows()
        except Exception:
            pass
        super().destroy_node()


def main(args=None) -> None:
    rclpy.init(args=args)
    node = VisionNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        node.get_logger().info('Shutting down vision_node (Ctrl+C).')
    finally:
        node.destroy_node()
        # If shutdown was already called from the callback, this is a no-op.
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
