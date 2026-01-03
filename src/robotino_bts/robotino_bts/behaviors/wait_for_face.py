# robotino_bts/behaviors/face_recognition.py
import py_trees
from py_trees.common import Access
from robotino_interfaces.srv import FaceRecog

class FaceRecognitionBehaviour(py_trees.behaviour.Behaviour):
    """
    BT node that calls /face_recog service asynchronously.
    - SUCCESS if at least one face is recognized
    - FAILURE otherwise (no faces, error)
    - Appends recognized name(s) to the specified guest list:
      guest_1 = ["Alice", "Alice", ...]
      guest_2 = ["Bob", ...]
    """
    def __init__(self, name, node, guest_key="guest_1"):
        super().__init__(name)
        self.node = node
        self.guest_key = guest_key  # "guest_1" or "guest_2"

        # Blackboard client - safe registration
        self.bb = py_trees.blackboard.Client(name=f"{name}_BB")
        self.bb.register_key(key=self.guest_key, access=Access.WRITE)
        self.bb.register_key("current_guest_name", py_trees.common.Access.WRITE)
    
        # ROS2 service client
        self.cli = self.node.create_client(FaceRecog, "/face_recog")
        self._face_result = None
        self._completed = False
      

    def initialise(self):
        self._completed = False
        self._face_result = None

        if not self.cli.wait_for_service(timeout_sec=1.0):
            self.node.get_logger().error("[FACE_BT] Service /face_recog not available")
            self._completed = True
            return

        req = FaceRecog.Request()
        req.name_request = []
        req.min_confidence = 0.0

        self._face_result = self.cli.call_async(req)
        self.node.get_logger().info(f"[FACE_BT] Request sent to /face_recog (target: {self.guest_key})")

    def update(self):
        if self._completed:
            return py_trees.common.Status.FAILURE

        if self._face_result is None:
            return py_trees.common.Status.FAILURE

        if not self._face_result.done():
            return py_trees.common.Status.RUNNING

        try:
            response = self._face_result.result()
        except Exception as e:
            self.node.get_logger().error(f"[FACE_BT] Face service call failed: {e}")
            self._completed = True
            return py_trees.common.Status.FAILURE

        names = response.name_response
        num_faces = len(names)

        if num_faces == 0:
            self.node.get_logger().info(f"[FACE_BT] No faces recognized (target: {self.guest_key})")
            self._completed = True
            return py_trees.common.Status.FAILURE

        # === FIXED BLACKBOARD ACCESS ===
        # Safely get the current list (avoid .get() with multiple args)
        if self.bb.exists(self.guest_key):
            guest_list = self.bb.get(self.guest_key)
        else:
            guest_list = []

        # Append new names
        guest_list.extend(names)

        # Write back
        self.bb.set(self.guest_key, guest_list)
        
        if guest_list and guest_list[0] != "unknown":
            self.bb.set("current_guest_name", guest_list[0])


        self.node.get_logger().info(
            f"[FACE_BT] Recognized {num_faces} face(s): {', '.join(names)} "
            f"→ appended to {self.guest_key} (total: {len(guest_list)})"
        )

        self._completed = True
        return py_trees.common.Status.SUCCESS