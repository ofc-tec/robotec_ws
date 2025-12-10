#!/usr/bin/env python3
import os
import yaml
import py_trees

import rclpy
from rclpy.node import Node
from ament_index_python.packages import get_package_share_directory

from robotino_bts.trees.roam_known_locs import create_behavior_tree


class BTExecutor(Node):
    def __init__(self):
        super().__init__("bt_executor")

        # Load known locations
        pkg_share = get_package_share_directory("robotino_bts")
        locations_path = os.path.join(pkg_share, "config", "known_locations.yaml")
        self.get_logger().info(f"Loading known locations from: {locations_path}")

        with open(locations_path, "r") as f:
            self.known_locations = yaml.safe_load(f)

        # Build the behavior tree
        self.tree = create_behavior_tree(self)
        py_trees.logging.level = py_trees.logging.Level.INFO

    def spin_tree(self):
        rate = self.create_rate(5.0)
        self.get_logger().info("Starting Behavior Tree...")

        while rclpy.ok():
            rclpy.spin_once(self, timeout_sec=0.1)
            self.tree.tick()

            if self.tree.root.status != py_trees.common.Status.RUNNING:
                self.get_logger().info(f"BT finished with status: {self.tree.root.status}")
                break

            rate.sleep()


def main(args=None):
    rclpy.init(args=args)
    node = BTExecutor()
    node.spin_tree()
    node.destroy_node()
    rclpy.shutdown()


if __name__ == "__main__":
    main()
