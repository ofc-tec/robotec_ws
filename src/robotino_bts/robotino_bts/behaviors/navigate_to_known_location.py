#!/usr/bin/env python3

import math
import py_trees

from rclpy.action import ActionClient
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import NavigateToPose


class NavToKnownLocation(py_trees.behaviour.Behaviour):
    """
    Navigate to a named location using Nav2.

    Expects:
        node.known_locations = {
            "kitchen": {"x": 1.0, "y": 2.0, "yaw": 1.57, "frame": "map"}
        }
    """

    def __init__(self, name, node, location_name, timeout_sec=60.0):
        super().__init__(name)
        self.node = node
        self.location_name = location_name
        self.timeout_sec = timeout_sec

        self._client = ActionClient(node, NavigateToPose, "navigate_to_pose")

        self._goal_future = None
        self._result_future = None
        self._goal_handle = None
        self._start_time = None

    def initialise(self):
        self._goal_future = None
        self._result_future = None
        self._goal_handle = None
        self._start_time = self.node.get_clock().now()

        if not self._client.wait_for_server(timeout_sec=1.0):
            self.node.get_logger().error("[NavToKnownLocation] Nav2 action not available")
            return

        locations = getattr(self.node, "known_locations", None)
        if not isinstance(locations, dict):
            self.node.get_logger().error("[NavToKnownLocation] node.known_locations missing")
            return

        pose = locations.get(self.location_name)
        if pose is None:
            self.node.get_logger().error(f"[NavToKnownLocation] Unknown location '{self.location_name}'")
            return

        x = float(pose["x"])
        y = float(pose["y"])
        yaw = float(pose.get("yaw", 0.0))
        frame = pose.get("frame", "map")

        goal = NavigateToPose.Goal()
        goal.pose = PoseStamped()
        goal.pose.header.frame_id = frame
        goal.pose.header.stamp = self.node.get_clock().now().to_msg()
        goal.pose.pose.position.x = x
        goal.pose.pose.position.y = y

        half = yaw * 0.5
        goal.pose.pose.orientation.z = math.sin(half)
        goal.pose.pose.orientation.w = math.cos(half)

        self.node.get_logger().info(
            f"[NavToKnownLocation] Going to '{self.location_name}' "
            f"({x:.2f}, {y:.2f}, yaw={yaw:.2f})"
        )

        self._goal_future = self._client.send_goal_async(goal)

    def update(self):
        if self._goal_future is None:
            return py_trees.common.Status.FAILURE

        elapsed = (
            self.node.get_clock().now().nanoseconds - self._start_time.nanoseconds
        ) * 1e-9
        if elapsed > self.timeout_sec:
            self.node.get_logger().warn("[NavToKnownLocation] Timeout")
            return py_trees.common.Status.FAILURE

        if self._goal_handle is None:
            if not self._goal_future.done():
                return py_trees.common.Status.RUNNING

            self._goal_handle = self._goal_future.result()
            if not self._goal_handle.accepted:
                self.node.get_logger().error("[NavToKnownLocation] Goal rejected")
                return py_trees.common.Status.FAILURE

            self._result_future = self._goal_handle.get_result_async()
            return py_trees.common.Status.RUNNING

        if not self._result_future.done():
            return py_trees.common.Status.RUNNING

        result = self._result_future.result()
        status = int(result.status)
        error_code = int(result.result.error_code)

        self.node.get_logger().info(
            f"[NavToKnownLocation] Result status={status} error_code={error_code}"
        )

        if status == 4 and error_code == 0:
            return py_trees.common.Status.SUCCESS

        return py_trees.common.Status.FAILURE
    def terminate(self, new_status):
        # If this behaviour stops being ticked while a goal is active, cancel it
        try:
            if self._goal_handle is not None:
                self.node.get_logger().warn(
                    f"[NavToKnownLocation] Terminate({new_status}), canceling Nav2 goal"
                )
                self._goal_handle.cancel_goal_async()
        except Exception as e:
            self.node.get_logger().warn(f"[NavToKnownLocation] Cancel failed: {e}")
