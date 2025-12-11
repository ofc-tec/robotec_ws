#!/usr/bin/env python3
# robotino_bts/task_manager.py

import os
import time

import rclpy
from rclpy.node import Node
from rclpy.executors import MultiThreadedExecutor
from ament_index_python.packages import get_package_share_directory

import yaml

from robotino_bts.trees.roam_known_locs import create_behavior_tree


class BTExecutor(Node):
    """
    Node that owns and ticks the Behavior Tree, while the ROS 2 executor
    spins to service action callbacks, subscriptions, etc.

    IMPORTANT: this node is also responsible for loading known_locations.yaml
    into self.known_locations so SetGoalFromLocation can work.
    """

    def __init__(self):
        super().__init__("bt_executor")

        # ------------------------------------------------------------------ #
        # 1) Load known locations from YAML into self.known_locations
        # ------------------------------------------------------------------ #
        try:
            pkg_share = get_package_share_directory("robotino_bts")
            known_locations_file = os.path.join(pkg_share, "config", "known_locations.yaml")
            self.get_logger().info(
                f"[bt_executor] Loading known locations from: {known_locations_file}"
            )

            with open(known_locations_file, "r") as f:
                data = yaml.safe_load(f) or {}

            if not isinstance(data, dict):
                self.get_logger().error(
                    f"[bt_executor] known_locations.yaml did not parse as a dict "
                    f"(got {type(data)}), using empty dict."
                )
                self.known_locations = {}
            else:
                self.known_locations = data
                self.get_logger().info(
                    f"[bt_executor] Loaded known locations: {list(self.known_locations.keys())}"
                )
        except Exception as e:
            self.get_logger().error(
                f"[bt_executor] Failed to load known_locations.yaml: {e}. "
                "Using empty dict."
            )
            self.known_locations = {}

        # ------------------------------------------------------------------ #
        # 2) Build the Behavior Tree using this node
        #     (SetGoalFromLocation will read self.known_locations)
        # ------------------------------------------------------------------ #
        self.tree = create_behavior_tree(self)

        try:
            self.tree.setup(timeout=15.0)
        except Exception as e:
            self.get_logger().error(f"[bt_executor] Error in tree.setup(): {e}")

        self.get_logger().info("[bt_executor] Behavior Tree setup complete")

    def tick_tree(self):
        """
        Tick the Behavior Tree once.
        """
        try:
            self.tree.tick()
        except Exception as e:
            self.get_logger().error(f"[bt_executor] Exception during BT tick: {e}")


def main(args=None):
    rclpy.init(args=args)

    node = BTExecutor()
    node.get_logger().info("[bt_executor] Starting Behavior Tree...")

    # Multi-threaded executor so action callbacks + BT can coexist
    executor = MultiThreadedExecutor()
    executor.add_node(node)

    try:
        while rclpy.ok():
            # 1) Let ROS2 process callbacks (actions, feedback, results, etc.)
            executor.spin_once(timeout_sec=0.05)

            # 2) Tick the Behavior Tree
            node.tick_tree()

            # Tick rate (20 Hz here)
            time.sleep(0.05)

    except KeyboardInterrupt:
        node.get_logger().info("[bt_executor] KeyboardInterrupt, shutting down...")
    finally:
        executor.shutdown()
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
