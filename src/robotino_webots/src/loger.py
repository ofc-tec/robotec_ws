#!/usr/bin/env python3
import csv
import math
from pathlib import Path

import rclpy
from nav_msgs.msg import Odometry
from rclpy.duration import Duration
from rclpy.node import Node
from rclpy.time import Time
from tf2_ros import Buffer, TransformException, TransformListener


def yaw_from_quaternion(q):
    siny_cosp = 2.0 * (q.w * q.z + q.x * q.y)
    cosy_cosp = 1.0 - 2.0 * (q.y * q.y + q.z * q.z)
    return math.atan2(siny_cosp, cosy_cosp)


def wrap_angle(angle):
    return math.atan2(math.sin(angle), math.cos(angle))


class RtabmapCorrectionLoger(Node):
    def __init__(self):
        super().__init__('loger')

        self.declare_parameter('odom_topic', '/odom')
        self.declare_parameter('map_frame', 'map')
        self.declare_parameter('odom_frame', 'odom')
        self.declare_parameter('base_frame', 'base_footprint')
        self.declare_parameter('log_period_sec', 1.0)
        self.declare_parameter('csv_path', '')

        self.odom_topic = self.get_parameter('odom_topic').value
        self.map_frame = self.get_parameter('map_frame').value
        self.odom_frame = self.get_parameter('odom_frame').value
        self.base_frame = self.get_parameter('base_frame').value
        self.csv_path = self.get_parameter('csv_path').value

        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        self.last_odom = None
        self.csv_file = None
        self.csv_writer = None

        if self.csv_path:
            path = Path(self.csv_path).expanduser()
            path.parent.mkdir(parents=True, exist_ok=True)
            self.csv_file = path.open('a', newline='')
            self.csv_writer = csv.writer(self.csv_file)
            if path.stat().st_size == 0:
                self.csv_writer.writerow([
                    'stamp_sec',
                    'odom_x', 'odom_y', 'odom_yaw',
                    'map_base_x', 'map_base_y', 'map_base_yaw',
                    'map_odom_x', 'map_odom_y', 'map_odom_yaw',
                    'correction_norm',
                ])

        self.create_subscription(Odometry, self.odom_topic, self.odom_callback, 20)
        self.create_timer(float(self.get_parameter('log_period_sec').value), self.log_sample)
        self.get_logger().info(
            f'Logging raw {self.odom_topic} against TF {self.map_frame}->{self.odom_frame} '
            f'and {self.map_frame}->{self.base_frame}'
        )

    def odom_callback(self, msg):
        self.last_odom = msg

    def lookup(self, target_frame, source_frame):
        return self.tf_buffer.lookup_transform(
            target_frame,
            source_frame,
            Time(),
            timeout=Duration(seconds=0.1),
        )

    def transform_xy_yaw(self, transform):
        t = transform.transform.translation
        r = transform.transform.rotation
        return t.x, t.y, yaw_from_quaternion(r)

    def log_sample(self):
        if self.last_odom is None:
            self.get_logger().warn(f'Waiting for {self.odom_topic}')
            return

        try:
            map_to_base = self.lookup(self.map_frame, self.base_frame)
            map_to_odom = self.lookup(self.map_frame, self.odom_frame)
        except TransformException as exc:
            self.get_logger().warn(f'Waiting for RTAB-Map correction TF: {exc}')
            return

        odom_pose = self.last_odom.pose.pose
        odom_x = odom_pose.position.x
        odom_y = odom_pose.position.y
        odom_yaw = yaw_from_quaternion(odom_pose.orientation)

        map_base_x, map_base_y, map_base_yaw = self.transform_xy_yaw(map_to_base)
        map_odom_x, map_odom_y, map_odom_yaw = self.transform_xy_yaw(map_to_odom)
        correction_norm = math.hypot(map_odom_x, map_odom_y)

        self.get_logger().info(
            'raw_odom=(%.3f, %.3f, %.1f deg) corrected_map_base=(%.3f, %.3f, %.1f deg) '
            'map_to_odom_correction=(%.3f, %.3f, %.1f deg | %.3f m)' % (
                odom_x,
                odom_y,
                math.degrees(odom_yaw),
                map_base_x,
                map_base_y,
                math.degrees(map_base_yaw),
                map_odom_x,
                map_odom_y,
                math.degrees(wrap_angle(map_odom_yaw)),
                correction_norm,
            )
        )

        if self.csv_writer:
            stamp = self.get_clock().now().nanoseconds / 1e9
            self.csv_writer.writerow([
                f'{stamp:.6f}',
                f'{odom_x:.6f}', f'{odom_y:.6f}', f'{odom_yaw:.6f}',
                f'{map_base_x:.6f}', f'{map_base_y:.6f}', f'{map_base_yaw:.6f}',
                f'{map_odom_x:.6f}', f'{map_odom_y:.6f}', f'{map_odom_yaw:.6f}',
                f'{correction_norm:.6f}',
            ])
            self.csv_file.flush()

    def destroy_node(self):
        if self.csv_file:
            self.csv_file.close()
        super().destroy_node()


def main():
    rclpy.init()
    node = RtabmapCorrectionLoger()
    try:
        rclpy.spin(node)
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == '__main__':
    main()
