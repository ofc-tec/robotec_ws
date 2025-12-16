#!/usr/bin/env python3
# robotino_bts/task_manager.py

import os
import time

import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from ament_index_python.packages import get_package_share_directory

import yaml

import py_trees
import py_trees_ros

from robotino_bts.trees.roam_known_locs import create_behavior_tree


class BTExecutor(Node):
    """
    Owns known_locations and builds the BT root. The py_trees_ros BehaviourTree
    will create its own internal node named /tree for introspection.
    """

    def __init__(self):
        super().__init__("bt_executor")

        # ------------------------------------------------------------------ #
        # 1) Load known locations into self.known_locations
        # ------------------------------------------------------------------ #
        try:
            pkg_share = get_package_share_directory("robotino_bts")
            known_locations_file = os.path.join(pkg_share, "config", "known_locations.yaml")
            self.get_logger().info(f"[bt_executor] Loading known locations from: {known_locations_file}")

            with open(known_locations_file, "r") as f:
                data = yaml.safe_load(f) or {}

            self.known_locations = data if isinstance(data, dict) else {}
            self.get_logger().info(f"[bt_executor] Loaded known locations: {list(self.known_locations.keys())}")
        except Exception as e:
            self.get_logger().error(f"[bt_executor] Failed to load known_locations.yaml: {e}. Using empty dict.")
            self.known_locations = {}

        # ------------------------------------------------------------------ #
        # 2) Build your tree (may return root Behaviour or a BehaviourTree)
        # ------------------------------------------------------------------ #
        built = create_behavior_tree(self)

        if isinstance(built, py_trees.behaviour.Behaviour):
            root = built
        elif hasattr(built, "root"):
            root = built.root
        else:
            root = built

        # ------------------------------------------------------------------ #
        # 3) ROS-enabled tree wrapper (creates services/topics for GUI/watcher)
        #    IMPORTANT: we will NOT pass node=self here.
        #    setup() will create its own internal node named "tree" => /tree
        # ------------------------------------------------------------------ #
        self.tree = py_trees_ros.trees.BehaviourTree(root)

        try:
            # Force creation of internal node '/tree' (default node_name="tree")
            self.tree.setup(node=None, node_name="tree", timeout=15.0)
        except Exception as e:
            self.get_logger().error(f"[bt_executor] Error in tree.setup(): {e}")

        self.get_logger().info("[bt_executor] Behavior Tree setup complete (introspection node: /tree)")

    def tick_tree(self):
        try:
            self.tree.tick()
        except Exception as e:
            self.get_logger().error(f"[bt_executor] Exception during BT tick: {e}")


def main(args=None):
    rclpy.init(args=args)

    node = BTExecutor()
    node.get_logger().info("[bt_executor] Starting Behavior Tree...")

    executor = MultiThreadedExecutor()
    executor.add_node(node)

    # IMPORTANT: also spin the internal py_trees_ros node (/tree)
    if getattr(node.tree, "node", None) is not None:
        executor.add_node(node.tree.node)

    try:
        while rclpy.ok():
            executor.spin_once(timeout_sec=0.05)
            node.tick_tree()
            time.sleep(0.05)
    except KeyboardInterrupt:
        node.get_logger().info("[bt_executor] KeyboardInterrupt, shutting down...")
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
