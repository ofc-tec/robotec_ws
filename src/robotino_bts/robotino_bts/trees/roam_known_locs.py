# robotino_bts/trees/roam_known_locs.py

import py_trees
from py_trees.common import Access

from robotino_bts.behaviors.init_blackboard import InitBlackboard
from robotino_bts.behaviors.set_goal_from_location import SetGoalFromLocation


def create_behavior_tree(node):
    """
    Simple BT:
      1) InitBlackboard(target_object="cup")
      2) SetGoalFromLocation("kitchen") -> writes goal_x/y/yaw
      3) LogGoalBehaviour -> just logs the goal from BB
    """
    root = py_trees.composites.Sequence(
        name="RoamKnownLocsRoot",
        memory=False
    )

    # 1) Init blackboard
    init_bb = InitBlackboard(target_object="cup")

    # 2) Set goal for one known location (e.g., "kitchen")
    set_kitchen = SetGoalFromLocation(
        name="SetGoalKitchen",
        node=node,
        location_name="kitchen",
    )

    # 3) Simple behaviour that logs the goal from the blackboard
    class LogGoalBehaviour(py_trees.behaviour.Behaviour):
        def __init__(self, name, node):
            super().__init__(name)
            self.node = node
            self.bb = py_trees.blackboard.Client(name="LogGoalBB")
            self.bb.register_key("goal_x", Access.READ)
            self.bb.register_key("goal_y", Access.READ)
            self.bb.register_key("goal_yaw", Access.READ)
            self.bb.register_key("current_location", Access.READ)
            self.bb.register_key("target_object", Access.READ)

        def update(self):
            loc = getattr(self.bb, "current_location", "unknown")
            x = getattr(self.bb, "goal_x", 0.0)
            y = getattr(self.bb, "goal_y", 0.0)
            yaw = getattr(self.bb, "goal_yaw", 0.0)
            target = getattr(self.bb, "target_object", "unknown")

            self.node.get_logger().info(
                f"[BT] LogGoal: location='{loc}', "
                f"goal=({x:.2f}, {y:.2f}, yaw={yaw:.2f}), "
                f"target_object='{target}'"
            )
            return py_trees.common.Status.SUCCESS

    log_goal = LogGoalBehaviour("LogGoal", node)

    root.add_children([init_bb, set_kitchen, log_goal])

    return py_trees.trees.BehaviourTree(root)
