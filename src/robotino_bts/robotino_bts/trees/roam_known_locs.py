# robotino_bts/trees/roam_known_locs.py

import py_trees
from py_trees.common import Access, OneShotPolicy

from robotino_bts.behaviors.init_blackboard_receptionist import InitBlackboard 
from robotino_bts.behaviors.navigate_to_known_location import NavToKnownLocation
# from robotino_bts.behaviors.set_goal_from_location import SetGoalFromLocation
# from robotino_bts.behaviors.navigate_to_pose import NavigateToPoseFromBB
from robotino_bts.behaviors.yolo_detect import YoloDetectBehaviour
from robotino_bts.behaviors.wait_for_face import FaceRecognitionBehaviour


def create_behavior_tree(node):
    """
    Minimal test tree:
      InitBlackboard -> LogBlackboard

    Wrapped in OneShot so it runs once.
    """

    node.get_logger().info("[BT] Building RoamKnownLocs tree (INIT+LOG test)")

    seq = py_trees.composites.Sequence(
        name="ReceptionistSeq",
        memory=True,
    )

    #####################################################
    init_bb = InitBlackboard()#host="jack")    ## init bb behavior
    
    
    #####################################################
    
    #####################################################
    goto_door = NavToKnownLocation(  ## navigate to known location behavior
        name="NavToDoor",
        node=node,
        #location_name="door",
        location_name="kitchen",
                            )

    #####################################################
    yolo_call = YoloDetectBehaviour(
        name="YoloCall",
        node=node,
    )

    face_call = FaceRecognitionBehaviour(
        name="FaceCall",
        node=node,
    )



    seq.add_children([
        init_bb,
        #log_bb,
        #goto_door,
        yolo_call,
        #face_call,
    ])

    root = py_trees.decorators.OneShot(
        name="ROOT",
        child=seq,
        policy=OneShotPolicy.ON_SUCCESSFUL_COMPLETION,
    )

    return py_trees.trees.BehaviourTree(root)
