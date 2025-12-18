# robotino_bts/behaviors/init_blackboard.py

import py_trees
from py_trees.common import Access


class InitBlackboard(py_trees.behaviour.Behaviour):
    """
    Initialize blackboard keys for the BT:
      - host: the host to receive guests (e.g. "jack")
      - guest_1: list to accumulate guest 1 detections later
      - guest_2: list to accumulate guest 2 detections later
    """

    def __init__(self, name="InitBlackboard", host="jack"):
        super().__init__(name)
        self.host = host

        # Blackboard client
        self.bb = py_trees.blackboard.Client(name="InitBB")
        self.bb.register_key("host", Access.WRITE)
        self.bb.register_key("guest_1", Access.WRITE)
        self.bb.register_key("guest_2", Access.WRITE)

    def update(self):
        self.bb.host = self.host
        self.bb.guest_1 = []
        self.bb.guest_2 = []

        self.logger.info(
            f"Blackboard initialized: host='{self.host}', "
            f"guest_1=[], guest_2=[]"
        )
        return py_trees.common.Status.SUCCESS

class LogBB(py_trees.behaviour.Behaviour):

    def __init__(self, name, node):
        super().__init__(name)
        self.node = node
        self.bb = py_trees.blackboard.Client(name="LogBB")
        self.bb.register_key("host", Access.READ)
        self.bb.register_key("guest_1", Access.READ)
        self.bb.register_key("guest_2", Access.READ)

    def update(self):
        host = getattr(self.bb, "host", None)
        g1 = getattr(self.bb, "guest_1", None)
        g2 = getattr(self.bb, "guest_2", None)
        self.node.get_logger().info(f"[BT] BB: host={host} guest_1={g1} guest_2={g2}")
        return py_trees.common.Status.SUCCESS
