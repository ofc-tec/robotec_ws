import operator
import py_trees
from py_trees.common import OneShotPolicy, ComparisonExpression

from robotino_bts.behaviors.init_blackboard_receptionist import InitBlackboard
from robotino_bts.behaviors.navigate_to_known_location import NavToKnownLocation
from robotino_bts.behaviors.wait_for_face import FaceRecognitionBehaviour
from robotino_bts.behaviors.wait_for_text import WaitForText
#from robotino_bts.behaviors.say_text import SayText
def SayText(name, node, text):
    class DummySayText(py_trees.behaviour.Behaviour):
        def __init__(self, name, node, text):
            super().__init__(name)
            self.node = node
            self.text = text

        def initialise(self):
            self.node.get_logger().info(f"[SAY_TEXT] {self.text}")

        def update(self):
            return py_trees.common.Status.SUCCESS

    return DummySayText(name, node, text)

def create_behavior_tree(node):

    seq = py_trees.composites.Sequence(
        name="ReceptionistDemo",
        memory=True
    )

    # -------------------------------------------------
    # Init
    init_bb = InitBlackboard(host="jack")

    intro = SayText(
        name="IntroTalk",
        node=node,
        text="Hello. I will go to the door. Please stand in front of me."
    )

    goto_door = NavToKnownLocation(
        name="NavToDoor",
        node=node,
        location_name="door",
    )

    # -------------------------------------------------
    # FACE BLOCK (<= 30s)
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

    face_selector = py_trees.composites.Selector(
        name="FaceOrTry",
        memory=False,
    )
    face_selector.add_children([has_face, face_try])

    face_timeout = py_trees.decorators.Timeout(
        name="FaceTimeout30s",
        child=face_selector,
        duration=30.0,
    )

    # -------------------------------------------------
    # SPEECH BLOCK (retry max 3)
    ask = SayText(
        name="AskNameDrink",
        node=node,
        text="What is your name and what drink would you like?"
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

    outro = SayText(
        name="OutroTalk",
        node=node,
        text="Nice to meet you. Thank you."
    )

    # -------------------------------------------------
    seq.add_children([
        init_bb,
        intro,
        goto_door,
        face_timeout,
        speech_retry,
        outro,
    ])

    root = py_trees.decorators.OneShot(
        name="ROOT",
        child=seq,
        policy=OneShotPolicy.ON_SUCCESSFUL_COMPLETION,
    )

    return py_trees.trees.BehaviourTree(root)
