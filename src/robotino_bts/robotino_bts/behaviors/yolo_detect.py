# robotino_bts/behaviors/yolo_detect.py

import py_trees
from py_trees.common import Access

from robotino_interfaces.srv import YoloDetect


class YoloDetectBehaviour(py_trees.behaviour.Behaviour):
    """
    BT node that calls the YOLO detection service asynchronously.

    - Sends an empty YoloDetect request in initialise()
    - Returns RUNNING until the future is done
    - On response, stores a summary in blackboard.detections_log:

        detections_log = [
          {
            "location": <current_location or 'unknown'>,
            "num_detections": N,
          },
          ...
        ]
    """

    def __init__(self, name, node):
        super().__init__(name)
        self.node = node

        # Blackboard client
        self.bb = py_trees.blackboard.Client(name=f"{name}_BB")
        self.bb.register_key("detections_log", Access.WRITE)
        self.bb.register_key("current_location", Access.READ)

        # ROS2 service client
        self.cli = self.node.create_client(YoloDetect, "yolo_detect")
        self.future = None
        self._done = False

    def initialise(self):
        self._done = False
        self.future = None

        if not self.cli.wait_for_service(timeout_sec=1.0):
            self.node.get_logger().error("[YOLO_BT] Service /yolo_detect not available")
            self._done = True
            return

        req = YoloDetect.Request()  # empty request
        self.future = self.cli.call_async(req)
        self.node.get_logger().info("[YOLO_BT] Request sent to /yolo_detect")

    def update(self):
        if self._done:
            return py_trees.common.Status.SUCCESS

        if self.future is None:
            # initialise() failed somehow
            return py_trees.common.Status.FAILURE

        if not self.future.done():
            # Still waiting for response
            return py_trees.common.Status.RUNNING

        # Response ready
        try:
            resp = self.future.result()
        except Exception as e:
            self.node.get_logger().error(f"[YOLO_BT] Service call failed: {e}")
            self._done = True
            return py_trees.common.Status.FAILURE

        # resp.detections is a Detection2DArray
        det_array = getattr(resp, "detections", None)
        if det_array is None:
            num = 0
        else:
            det_list = getattr(det_array, "detections", [])
            num = len(det_list)

        location = getattr(self.bb, "current_location", "unknown")

        # Append to detections_log
        log = self.bb.detections_log or []
        log.append({
            "location": location,
            "num_detections": num,
        })
        self.bb.detections_log = log

        self.node.get_logger().info(
            f"[YOLO_BT] At location '{location}' got {num} detections. "
            f"detections_log length = {len(log)}"
        )

        self._done = True
        return py_trees.common.Status.SUCCESS
