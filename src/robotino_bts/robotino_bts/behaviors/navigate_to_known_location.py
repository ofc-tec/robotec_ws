#!/usr/bin/env python3
import math
import py_trees

from rclpy.action import ActionClient
from geometry_msgs.msg import PoseStamped
from nav2_msgs.action import NavigateToPose
from nav_msgs.msg import Path
from std_msgs.msg import Float32, Bool


class NavToKnownLocation(py_trees.behaviour.Behaviour):
    """
    Navigate to a named location using Nav2, but do a "pre-rotate" hack:
    - Send goal (so planner creates a plan)
    - When first plan arrives, cancel goal immediately and publish /target_yaw
    - Wait a short time, resend the same goal

    Expects:
        node.known_locations = {
            "kitchen": {"x": 1.0, "y": 2.0, "yaw": 1.57, "frame": "map"}
        }
    """

    def __init__(self, name, node, location_name, timeout_sec=60.0,
                 plan_topic="/transformed_global_plan",
                 yaw_topic="/target_yaw",
                 lookahead_idx=3,
                 pre_rotate_wait_sec=1.0):
        super().__init__(name)
        self.node = node
        self.location_name = location_name
        self.timeout_sec = float(timeout_sec)

        self.plan_topic = plan_topic
        self.yaw_topic = yaw_topic
        self.lookahead_idx = int(lookahead_idx)
        self.pre_rotate_wait_sec = float(pre_rotate_wait_sec)

        self._client = ActionClient(node, NavigateToPose, "navigate_to_pose")

        # Pub/sub created ONCE (not in initialise)
        self._yaw_pub = node.create_publisher(Float32, self.yaw_topic, 10)
        self._plan_sub = node.create_subscription(Path, self.plan_topic, self._on_plan, 10)

        # Runtime state
        self._goal_msg = None
        self._goal_future = None
        self._result_future = None
        self._goal_handle = None
        self._start_time = None

        self._latest_plan = None
        self._saw_plan = False
        self._canceled_once = False
        self._resent_after_align = False
        self._yaw_publish_time = None
        self._yaw_aligned = False

        self._yaw_aligned_sub = node.create_subscription(
            Bool,
            "/yaw_aligned",
            self._on_yaw_aligned,
            10
        )
    # ----------------------------
    # Helpers
    # ----------------------------
    def _on_yaw_aligned(self, msg: Bool):
        self._yaw_aligned = bool(msg.data)

    def _on_plan(self, msg: Path):
        if msg is None or len(msg.poses) < 2:
            return
        self._latest_plan = msg
        self._saw_plan = True

    def _yaw_from_plan(self, plan: Path, lookahead_idx: int):
        poses = plan.poses
        i = min(max(1, lookahead_idx), len(poses) - 1)
        x0 = poses[0].pose.position.x
        y0 = poses[0].pose.position.y
        x1 = poses[i].pose.position.x
        y1 = poses[i].pose.position.y
        return math.atan2(y1 - y0, x1 - x0)

    # ----------------------------
    # PyTrees hooks
    # ----------------------------
    def initialise(self):
        # reset per-tick run state
        self._goal_future = None
        self._result_future = None
        self._goal_handle = None
        self._start_time = self.node.get_clock().now()

        self._latest_plan = None
        self._saw_plan = False
        self._canceled_once = False
        self._resent_after_align = False
        self._yaw_publish_time = None
        self._yaw_aligned = False


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

        # store the goal for resending later
        self._goal_msg = goal

        self.node.get_logger().info(
            f"[NavToKnownLocation] Going to '{self.location_name}' "
            f"({x:.2f}, {y:.2f}, yaw={yaw:.2f})"
        )

        # send first time
        self._goal_future = self._client.send_goal_async(self._goal_msg)

    def update(self):
        if self._goal_future is None:
            return py_trees.common.Status.FAILURE

        elapsed = (self.node.get_clock().now().nanoseconds - self._start_time.nanoseconds) * 1e-9
        if elapsed > self.timeout_sec:
            self.node.get_logger().warn("[NavToKnownLocation] Timeout")
            return py_trees.common.Status.FAILURE

        # Wait until we have a goal handle (needed to cancel)
        if self._goal_handle is None:
            if not self._goal_future.done():
                return py_trees.common.Status.RUNNING

            self._goal_handle = self._goal_future.result()
            if not self._goal_handle.accepted:
                self.node.get_logger().error("[NavToKnownLocation] Goal rejected")
                return py_trees.common.Status.FAILURE

            self._result_future = self._goal_handle.get_result_async()
            return py_trees.common.Status.RUNNING

        # --- cancel-on-plan + publish yaw (once) ---
        if self._saw_plan and (not self._canceled_once):
            try:
                self.node.get_logger().warn("[NavToKnownLocation] Plan ready -> canceling to pre-rotate")
                self._goal_handle.cancel_goal_async()
            except Exception as e:
                self.node.get_logger().warn(f"[NavToKnownLocation] Cancel failed: {e}")

            try:
                yaw_path = self._yaw_from_plan(self._latest_plan, self.lookahead_idx)
                msg = Float32()
                msg.data = float(yaw_path)
                self._yaw_pub.publish(msg)
                self._yaw_publish_time = self.node.get_clock().now()
                self.node.get_logger().info(f"[NavToKnownLocation] Published {self.yaw_topic}={yaw_path:.2f} rad")
            except Exception as e:
                self.node.get_logger().warn(f"[NavToKnownLocation] Yaw-from-plan failed: {e}")

            self._canceled_once = True
            self._saw_plan = False
            return py_trees.common.Status.RUNNING

        # --- after publishing yaw, wait a bit, then resend goal once ---
               # --- after publishing yaw, wait until alignment succeeds ---
        if self._canceled_once and (not self._resent_after_align):
            if not self._yaw_aligned:
                # still rotating
                return py_trees.common.Status.RUNNING

            self.node.get_logger().warn(
                "[NavToKnownLocation] Yaw aligned, resending goal"
            )

            self._goal_future = self._client.send_goal_async(self._goal_msg)
            self._goal_handle = None
            self._result_future = None
            self._resent_after_align = True
            return py_trees.common.Status.RUNNING


        # normal nav result processing
        if self._result_future is None or (not self._result_future.done()):
            return py_trees.common.Status.RUNNING

        result = self._result_future.result()
        status = int(result.status)
        error_code = int(result.result.error_code)

        self.node.get_logger().info(f"[NavToKnownLocation] Result status={status} error_code={error_code}")

        # STATUS_SUCCEEDED == 4
        if status == 4 and error_code == 0:
            return py_trees.common.Status.SUCCESS

        return py_trees.common.Status.FAILURE

    def terminate(self, new_status):
        try:
            if self._goal_handle is not None:
                self.node.get_logger().warn(
                    f"[NavToKnownLocation] Terminate({new_status}), canceling Nav2 goal"
                )
                self._goal_handle.cancel_goal_async()
        except Exception as e:
            self.node.get_logger().warn(f"[NavToKnownLocation] Cancel failed: {e}")
