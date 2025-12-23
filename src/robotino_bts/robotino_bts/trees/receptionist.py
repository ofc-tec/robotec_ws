# robotino_bts/trees/receptionist_demo.py
#
# Full drop-in file (NO dummy SayText).
# Uses your real TTS service:
#   Service: /tts/talk
#   Type:    robotino_interfaces/srv/Talk
#
# Behavior notes:
# - SayTextBehaviour sends a service request and returns:
#     RUNNING while waiting for the service reply
#     SUCCESS when reply success=True
#     FAILURE otherwise
# - If you pass wait=True in the request, the TTS server blocks until finished speaking.
#   So this BT node effectively becomes "sync speech" (sequence-friendly).

import operator

import py_trees
from py_trees.common import OneShotPolicy, ComparisonExpression

from robotino_interfaces.srv import Talk

from robotino_bts.behaviors.init_blackboard_receptionist import InitBlackboard
from robotino_bts.behaviors.navigate_to_known_location import NavToKnownLocation
from robotino_bts.behaviors.wait_for_face import FaceRecognitionBehaviour
from robotino_bts.behaviors.wait_for_text import WaitForText


class SayTextBehaviour(py_trees.behaviour.Behaviour):
    """
    Calls /tts/talk (robotino_interfaces/srv/Talk).

    If request.wait=True, the server will block until speech finishes
    and then reply -> this BT node will be RUNNING until it gets that reply.

    If request.wait=False, the server replies immediately -> this node will complete fast.
    """

    def __init__(self, name, node, text: str, wait: bool = True, service_name: str = "/tts/talk"):
        super().__init__(name)
        self.node = node
        self.text = text
        self.wait = wait
        self.service_name = service_name

        self._client = None
        self._future = None

    def setup(self, **kwargs):
        # Called by py_trees_ros behaviour tree if used; safe to keep.
        if self._client is None:
            self._client = self.node.create_client(Talk, self.service_name)

    def initialise(self):
        if self._client is None:
            self._client = self.node.create_client(Talk, self.service_name)

        # If service isn't available, fail fast (makes debugging obvious).
        if not self._client.wait_for_service(timeout_sec=0.2):
            self.node.get_logger().error(f"[SAY_TEXT] Service not available: {self.service_name}")
            self._future = None
            return

        req = Talk.Request()
        req.text = self.text
        req.wait = bool(self.wait)

        self.node.get_logger().info(f"[SAY_TEXT] Calling {self.service_name} wait={self.wait}: {self.text}")
        self._future = self._client.call_async(req)

    def update(self):
        if self._future is None:
            return py_trees.common.Status.FAILURE

        if not self._future.done():
            return py_trees.common.Status.RUNNING

        try:
            resp = self._future.result()
        except Exception as e:
            self.node.get_logger().error(f"[SAY_TEXT] Service call failed: {e}")
            return py_trees.common.Status.FAILURE

        if getattr(resp, "success", False):
            return py_trees.common.Status.SUCCESS

        msg = getattr(resp, "message", "unknown error")
        self.node.get_logger().warn(f"[SAY_TEXT] TTS returned failure: {msg}")
        return py_trees.common.Status.FAILURE

    def terminate(self, new_status):
        # Do not try to cancel the service call (rclpy doesn't cancel service futures reliably).
        pass


def create_behavior_tree(node):
    seq = py_trees.composites.Sequence(
        name="ReceptionistDemo",
        memory=True
    )

    # -------------------------------------------------
    # Init + intro + navigate
    init_bb = InitBlackboard(host="jack")

    intro = SayTextBehaviour(
        name="IntroTalk",
        node=node,
        text="Hello. I will go to the door. Please stand in front of me.",
        wait=True,
    )

    goto_door = NavToKnownLocation(
        name="NavToDoor",
        node=node,
        location_name="door",
    )

    # -------------------------------------------------
    # FACE BLOCK (<= 30s)
    # SUCCESS only if bb.face_ok == True; timeout without face => FAIL.
    has_face = py_trees.behaviours.CheckBlackboardVariableValue(
        name="HasFace?",
        check=ComparisonExpression(
            variable="face_ok",
            value=True,
            operator=operator.eq,
        ),
    )

    face_try = FaceRecognitionBehaviour(
        name="AcquireFace",
        node=node,
    )

    face_loop = py_trees.composites.Selector(
        name="FaceLoop",
        memory=False,
    )
    face_loop.add_children([has_face, face_try])

    face_timeout = py_trees.decorators.Timeout(
        name="FaceTimeout30s",
        child=face_loop,
        duration=30.0,
    )

    face_gate = py_trees.composites.Sequence(
        name="FaceGate",
        memory=True,
    )
    face_gate.add_children([face_timeout, has_face])

    # -------------------------------------------------
    # SPEECH BLOCK (retry max 3)
    ask = SayTextBehaviour(
        name="AskNameDrink",
        node=node,
        text="What is your name and what drink would you like?",
        wait=True,
    )

    listen = WaitForText(
        name="ListenText",
        node=node,
    )

    has_name = py_trees.behaviours.CheckBlackboardVariableValue(
        name="HasName?",
        check=ComparisonExpression(
            variable="current_guest_name",
            value="",
            operator=operator.ne,
        ),
    )

    has_drink = py_trees.behaviours.CheckBlackboardVariableValue(
        name="HasDrink?",
        check=ComparisonExpression(
            variable="current_guest_drink",
            value="",
            operator=operator.ne,
        ),
    )

    got_both = py_trees.composites.Sequence(
        name="GotNameAndDrink",
        memory=True,
    )
    got_both.add_children([has_name, has_drink])

    ask_and_listen = py_trees.composites.Sequence(
        name="AskAndListen",
        memory=True,
    )
    ask_and_listen.add_children([ask, listen, got_both])

    speech_retry = py_trees.decorators.Retry(
        name="SpeechRetry3",
        child=ask_and_listen,
        num_failures=3,
    )

    outro = SayTextBehaviour(
        name="OutroTalk",
        node=node,
        text="Nice to meet you. Thank you.",
        wait=True,
    )

    # -------------------------------------------------
    seq.add_children([
        init_bb,
        intro,
        goto_door,
        face_gate,
        speech_retry,
        outro,
    ])

    root = py_trees.decorators.OneShot(
        name="ROOT",
        child=seq,
        policy=OneShotPolicy.ON_SUCCESSFUL_COMPLETION,
    )

    return py_trees.trees.BehaviourTree(root)
