# robotino_bts/trees/roam_known_locs.py

import py_trees
from py_trees.common import Access, OneShotPolicy

from robotino_bts.behaviors.init_blackboard import InitBlackboard
from robotino_bts.behaviors.set_goal_from_location import SetGoalFromLocation
from robotino_bts.behaviors.navigate_to_pose import NavigateToPoseFromBB
from robotino_bts.behaviors.yolo_detect import YoloDetectBehaviour


def create_behavior_tree(node):
    """
    Build the 'roam known locations' behavior tree:

      InitBlackboard -> SetGoal(kitchen) -> NavigateToPose -> YOLO -> LogDetections

    Wrapped in a OneShot decorator so the whole sequence runs ONCE and then
    never restarts on subsequent ticks.
    """

    # Inner sequence: the actual pipeline
    seq = py_trees.composites.Sequence(
        name="RoamKnownLocsSeq",
        memory=True,   # remember child SUCCESS state while running
    )

    # 1) Initialise blackboard
    init_bb = InitBlackboard(target_object="cup")

    # 2) Set goal for known location "kitchen"
    set_kitchen = SetGoalFromLocation(
        name="SetGoalKitchen",
        node=node,
        location_name="kitchen",
    )

    # 3) Navigate using Nav2
    nav_to_kitchen = NavigateToPoseFromBB(
        name="NavToKitchen",
        node=node,
        frame_id="map",
    )

    # 4) Call YOLO after navigation
    yolo_after_nav = YoloDetectBehaviour(
        name="YoloAfterKitchen",
        node=node,
    )

    # 5) Log detections_log content
    class LogDetections(py_trees.behaviour.Behaviour):
        def __init__(self, name, node):
            super().__init__(name)
            self.node = node
            self.bb = py_trees.blackboard.Client(name="LogDetBB")
            self.bb.register_key("detections_log", Access.READ)

        def update(self):
            log = getattr(self.bb, "detections_log", []) or []
            self.node.get_logger().info(f"[BT] Detections log: {log}")
            return py_trees.common.Status.SUCCESS

    log_det = LogDetections("LogDetections", node)

    seq.add_children([
        init_bb,
        set_kitchen,
        nav_to_kitchen,
        yolo_after_nav,
        log_det,
    ])

    # Wrap sequence in a OneShot decorator:
    # after the first SUCCESS, children are never ticked again.
    root = py_trees.decorators.OneShot(
        name="RoamKnownLocsRoot",
        child=seq,
        policy=OneShotPolicy.ON_SUCCESSFUL_COMPLETION,
    )

    return py_trees.trees.BehaviourTree(root)
