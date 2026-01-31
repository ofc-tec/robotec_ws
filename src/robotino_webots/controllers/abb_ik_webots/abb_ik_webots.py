#!/usr/bin/env python3
"""
ABB IRB4600 Webots controller:
- Uses Webots-exported URDF + ikpy for IK
- Subscribes to ROS2 topic /abb_target (geometry_msgs/Point) to move end-effector
- If no ROS target has been received, it keeps the original demo behavior:
  * Draw circle for a few seconds
  * Then wait (or you can keep the sphere-follow loop if you want)
"""

import sys
import math
import tempfile

from controller import Supervisor

# --- ikpy import (same behavior as Webots demo) ---
try:
    import ikpy
    from ikpy.chain import Chain
except ImportError:
    sys.exit('The "ikpy" Python module is not installed. Install with: pip install ikpy')

if ikpy.__version__[0] < '3':
    sys.exit('ikpy version too old. Need >= 3.0')

# --- ROS2 (optional but expected) ---
import rclpy
from rclpy.node import Node
from geometry_msgs.msg import Point


IKPY_MAX_ITERATIONS = 4


class TargetNode(Node):
    def __init__(self):
        super().__init__('abb_ik_webots')
        self.target = None  # (x,y,z) in the IK frame used below
        self.create_subscription(Point, '/abb_target', self.cb, 10)

    def cb(self, msg: Point):
        self.target = (msg.x, msg.y, msg.z)


def main():
    # Initialize Webots Supervisor
    supervisor = Supervisor()
    time_step = int(4 * supervisor.getBasicTimeStep())

    # Init ROS2 (inside Webots controller process)
    rclpy.init(args=None)
    rosnode = TargetNode()

    # Export URDF from Webots and build IK chain
    with tempfile.NamedTemporaryFile(suffix='.urdf', delete=False) as f:
        urdf_path = f.name
        f.write(supervisor.getUrdf().encode('utf-8'))

    arm_chain = Chain.from_urdf_file(
        urdf_path,
        # same as the Webots sample (adjust only if your joint count differs)
        active_links_mask=[False, True, True, True, True, True, True, False]
    )

    # Initialize motors + sensors
    motors = []
    for link in arm_chain.links:
        if 'motor' in link.name:
            motor = supervisor.getDevice(link.name)
            motor.setVelocity(1.0)
            ps = motor.getPositionSensor()
            ps.enable(time_step)
            motors.append(motor)

    # Optional pen
    pen = None
    try:
        pen = supervisor.getDevice('pen')
    except Exception:
        pen = None

    # --- Phase 0: draw a circle (same as sample) ---
    print('[abb_ik_ros] Draw a circle demo...')
    while supervisor.step(time_step) != -1:
        t = supervisor.getTime()

        # circle trajectory in the IK frame the sample expects
        x = 0.25 * math.cos(t) + 1.1
        y = 0.25 * math.sin(t) - 0.95
        z = 0.05

        initial_position = [0] + [m.getPositionSensor().getValue() for m in motors] + [0]
        ik = arm_chain.inverse_kinematics(
            [x, y, z],
            max_iter=IKPY_MAX_ITERATIONS,
            initial_position=initial_position
        )

        # sample’s actuation logic
        for i in range(3):
            motors[i].setPosition(ik[i + 1])
        motors[4].setPosition(-ik[2] - ik[3] + math.pi / 2)
        motors[5].setPosition(ik[1])

        if t > 2 * math.pi + 1.5:
            break
        elif t > 1.5 and pen is not None:
            pen.write(True)

    # stop pen after demo
    if pen is not None:
        pen.write(False)

    # --- Phase 1: ROS target control ---
    print('[abb_ik_ros] Waiting for /abb_target (geometry_msgs/Point). Publish x,y,z to move the arm.')
    print("Example: ros2 topic pub -1 /abb_target geometry_msgs/msg/Point \"{x: 0.35, y: 0.10, z: 0.15}\"")

    while supervisor.step(time_step) != -1:
        rclpy.spin_once(rosnode, timeout_sec=0.0)

        if rosnode.target is None:
            continue

        x, y, z = rosnode.target

        initial_position = [0] + [m.getPositionSensor().getValue() for m in motors] + [0]
        ik = arm_chain.inverse_kinematics(
            [x, y, z],
            max_iter=IKPY_MAX_ITERATIONS,
            initial_position=initial_position
        )

        for i in range(len(motors)):
            motors[i].setPosition(ik[i + 1])


if __name__ == '__main__':
    main()
