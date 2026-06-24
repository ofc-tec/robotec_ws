#!/usr/bin/env python3
"""
Points-only Plane Segmentation Detector Node
Uses RANSAC to detect horizontal planes in point clouds
Adapted from catkin_extras segmentation utilities
"""

import rclpy
from rclpy.node import Node
from rclpy.time import Time
import numpy as np
import cv2

from sensor_msgs.msg import PointCloud2, PointField
from sensor_msgs.msg import Image
from sensor_msgs_py import point_cloud2
from std_msgs.msg import Empty
from geometry_msgs.msg import PoseStamped
from vision_msgs.msg import Detection2DArray, Detection2D, ObjectHypothesisWithPose, BoundingBox2D
from robotino_interfaces.srv import YoloDetect
from tf2_ros import Buffer, TransformListener
from tf2_sensor_msgs.tf2_sensor_msgs import do_transform_cloud

try:
    import open3d as o3d
    O3D_AVAILABLE = True
except ImportError:
    O3D_AVAILABLE = False


class PlaneDetectorNode(Node):
    def __init__(self):
        super().__init__('plane_detector_node')
        
        if not O3D_AVAILABLE:
            self.get_logger().warn("Open3D not available. Falling back to NumPy RANSAC.")
        
        # Parameters
        self.declare_parameter('cloud_topic', '/kinect/points')
        self.declare_parameter('distance_threshold', 0.02)
        self.declare_parameter('ransac_n', 3)
        self.declare_parameter('num_iterations', 1000)
        self.declare_parameter('horizontal_only', False)
        self.declare_parameter('normal_threshold', 0.1)
        self.declare_parameter('min_plane_size', 100)
        self.declare_parameter('max_planes', 5)
        self.declare_parameter('max_ransac_points', 20000)
        self.declare_parameter('random_seed', 0)
        self.declare_parameter('target_frame', 'odom')
        self.declare_parameter('trigger_topic', '/vision/segment_once')
        self.declare_parameter('service_name', '/tabletop_detect')
        self.declare_parameter('debug_image_topic', '/vision/tabletop_debug_image')
        self.declare_parameter('debug_stage', 'selected_plane')
        self.declare_parameter('process_on_trigger', True)
        self.declare_parameter('publish_object_candidates', True)
        self.declare_parameter('object_min_height', 0.005)
        self.declare_parameter('object_max_height', 0.10)
        self.declare_parameter('table_normal_z_threshold', 0.85)
        self.declare_parameter('min_table_height', 0.05)
        self.declare_parameter('table_mask_kernel_size', 35)
        self.declare_parameter('table_mask_close_iterations', 2)
        self.declare_parameter('table_mask_dilate_iterations', 1)
        self.declare_parameter('object_mask_kernel_size', 5)
        self.declare_parameter('object_mask_open_iterations', 1)
        self.declare_parameter('object_mask_close_iterations', 2)
        self.declare_parameter('min_contour_area', 80.0)
        self.declare_parameter('max_contour_area', 50000.0)
        
        self.cloud_topic = self.get_parameter('cloud_topic').get_parameter_value().string_value
        self.distance_threshold = self.get_parameter('distance_threshold').get_parameter_value().double_value
        self.ransac_n = self.get_parameter('ransac_n').get_parameter_value().integer_value
        self.num_iterations = self.get_parameter('num_iterations').get_parameter_value().integer_value
        self.horizontal_only = self.get_parameter('horizontal_only').get_parameter_value().bool_value
        self.normal_threshold = self.get_parameter('normal_threshold').get_parameter_value().double_value
        self.min_plane_size = self.get_parameter('min_plane_size').get_parameter_value().integer_value
        self.max_planes = self.get_parameter('max_planes').get_parameter_value().integer_value
        self.max_ransac_points = self.get_parameter('max_ransac_points').get_parameter_value().integer_value
        self.random_seed = self.get_parameter('random_seed').get_parameter_value().integer_value
        self.target_frame = self.get_parameter('target_frame').get_parameter_value().string_value
        self.trigger_topic = self.get_parameter('trigger_topic').get_parameter_value().string_value
        self.service_name = self.get_parameter('service_name').get_parameter_value().string_value
        self.debug_image_topic = self.get_parameter(
            'debug_image_topic'
        ).get_parameter_value().string_value
        self.debug_stage = self.get_parameter(
            'debug_stage'
        ).get_parameter_value().string_value
        self.process_on_trigger = self.get_parameter('process_on_trigger').get_parameter_value().bool_value
        self.publish_object_candidates = self.get_parameter(
            'publish_object_candidates'
        ).get_parameter_value().bool_value
        self.object_min_height = self.get_parameter('object_min_height').get_parameter_value().double_value
        self.object_max_height = self.get_parameter('object_max_height').get_parameter_value().double_value
        self.table_normal_z_threshold = self.get_parameter(
            'table_normal_z_threshold'
        ).get_parameter_value().double_value
        self.min_table_height = self.get_parameter(
            'min_table_height'
        ).get_parameter_value().double_value
        self.table_mask_kernel_size = self.get_parameter(
            'table_mask_kernel_size'
        ).get_parameter_value().integer_value
        self.table_mask_close_iterations = self.get_parameter(
            'table_mask_close_iterations'
        ).get_parameter_value().integer_value
        self.table_mask_dilate_iterations = self.get_parameter(
            'table_mask_dilate_iterations'
        ).get_parameter_value().integer_value
        self.object_mask_kernel_size = self.get_parameter(
            'object_mask_kernel_size'
        ).get_parameter_value().integer_value
        self.object_mask_open_iterations = self.get_parameter(
            'object_mask_open_iterations'
        ).get_parameter_value().integer_value
        self.object_mask_close_iterations = self.get_parameter(
            'object_mask_close_iterations'
        ).get_parameter_value().integer_value
        self.min_contour_area = self.get_parameter('min_contour_area').get_parameter_value().double_value
        self.max_contour_area = self.get_parameter('max_contour_area').get_parameter_value().double_value
        self.rng = np.random.default_rng(self.random_seed)
        self.latest_cloud_msg = None
        
        self.get_logger().info(f'[plane_detector] Using cloud_topic: {self.cloud_topic}')
        self.get_logger().info(f'[plane_detector] Distance threshold: {self.distance_threshold}')
        self.get_logger().info(f'[plane_detector] Horizontal planes only: {self.horizontal_only}')
        self.get_logger().info(f'[plane_detector] Process on trigger: {self.process_on_trigger}')
        
        # TF handling
        self.tf_buffer = Buffer()
        self.tf_listener = TransformListener(self.tf_buffer, self)
        
        # Publishers for detected planes
        self.plane_cloud_pub = self.create_publisher(
            PointCloud2,
            'detected_plane_cloud',
            10
        )
        
        self.remaining_cloud_pub = self.create_publisher(
            PointCloud2,
            'remaining_cloud',
            10
        )

        self.object_candidate_cloud_pub = self.create_publisher(
            PointCloud2,
            'object_candidate_cloud',
            10
        )

        self.debug_image_pub = self.create_publisher(
            Image,
            self.debug_image_topic,
            10
        )
        
        # Subscriber
        self.subscription = self.create_subscription(
            PointCloud2,
            self.cloud_topic,
            self.cloud_callback,
            10
        )

        self.trigger_subscription = self.create_subscription(
            Empty,
            self.trigger_topic,
            self.trigger_callback,
            10
        )

        self.detect_service = self.create_service(
            YoloDetect,
            self.service_name,
            self.handle_tabletop_detect
        )
        
        self.get_logger().info("[plane_detector] Node initialized and waiting for point clouds...")
    
    def cloud_callback(self, msg: PointCloud2):
        """Process incoming point cloud and detect planes"""
        self.latest_cloud_msg = msg
        if self.process_on_trigger:
            return
        self.process_cloud(msg)

    def trigger_callback(self, _msg: Empty):
        if self.latest_cloud_msg is None:
            self.get_logger().warn("[plane_detector] Segment trigger received, but no cloud has arrived yet")
            return

        self.get_logger().info("[plane_detector] Segment trigger received")
        self.process_cloud(self.latest_cloud_msg)

    def handle_tabletop_detect(self, _request, response: YoloDetect.Response):
        response.class_names = []
        response.poses = []
        response.detections = Detection2DArray()

        if self.latest_cloud_msg is None:
            self.get_logger().warn("[plane_detector] Tabletop service called, but no cloud has arrived yet")
            return response

        self.get_logger().info("[plane_detector] Tabletop detect service called")
        result = self.process_cloud(self.latest_cloud_msg)
        if not result:
            return response

        response.detections = result['detections']
        response.class_names = result['class_names']
        response.poses = result['poses']
        return response

    def process_cloud(self, msg: PointCloud2):
        try:
            source_frame = msg.header.frame_id

            corrected_cloud = self.transform_xyz_only_cloud(msg, source_frame)
            xyz, valid = self.pointcloud2_to_organized_xyz(
                corrected_cloud,
                organized_height=msg.height,
                organized_width=msg.width
            )

            if xyz.ndim != 3:
                self.get_logger().warn(
                    "[plane_detector] Object contour extraction needs an organized cloud; "
                    "falling back to flat plane segmentation"
                )
                points = self.pointcloud2_to_xyz_array(corrected_cloud)
                if len(points) == 0:
                    self.get_logger().warn("[plane_detector] No valid points in cloud")
                    return
                self.process_flat_cloud(points, corrected_cloud.header)
                return None

            flat_xyz = xyz.reshape((-1, 3))
            flat_valid = valid.reshape((-1,))
            valid_flat_indices = np.flatnonzero(flat_valid)
            valid_points = flat_xyz[valid_flat_indices]

            if len(valid_points) == 0:
                self.get_logger().warn("[plane_detector] No valid points in cloud")
                return None

            planes_info, remaining_valid_indices = self.detect_planes_ransac(valid_points)
            
            if planes_info:
                all_plane_flat_indices = []
                for i, plane_data in enumerate(planes_info):
                    plane_coeffs = plane_data['coefficients']
                    inlier_indices = valid_flat_indices[plane_data['inliers']]
                    all_plane_flat_indices.append(inlier_indices)
                    
                    self.get_logger().info(
                        f"[plane_detector] Plane {i}: coefficients={plane_coeffs}, "
                        f"inliers={len(inlier_indices)}"
                    )

                plane_indices = np.concatenate(all_plane_flat_indices)
                plane_cloud = self.numpy_to_pointcloud2(
                    flat_xyz[plane_indices],
                    corrected_cloud.header
                )
                self.plane_cloud_pub.publish(plane_cloud)

                remaining_indices = valid_flat_indices[remaining_valid_indices]
                remaining_cloud = self.numpy_to_pointcloud2(
                    flat_xyz[remaining_indices],
                    corrected_cloud.header
                )
                self.remaining_cloud_pub.publish(remaining_cloud)

                if self.publish_object_candidates:
                    table_plane = self.select_table_plane(valid_points, planes_info)
                    object_indices, objects = self.extract_tabletop_objects(
                        xyz,
                        valid,
                        valid_flat_indices,
                        table_plane,
                    )
                    object_cloud = self.numpy_to_pointcloud2(
                        flat_xyz[object_indices],
                        corrected_cloud.header
                    )
                    self.object_candidate_cloud_pub.publish(object_cloud)
                    self.get_logger().info(
                        f"[plane_detector] Tabletop candidates: {len(object_indices)} points, "
                        f"{len(objects)} contours "
                        f"(height {self.object_min_height:.3f}-{self.object_max_height:.3f} m)"
                    )
                    return self.make_yolo_style_result(
                        objects,
                        corrected_cloud.header,
                    )
            else:
                self.get_logger().debug("[plane_detector] No planes matched the configured filters")
                return None
                
        except Exception as e:
            self.get_logger().error(f"[plane_detector] Error in callback: {e}", exc_info=True)
            return None

    def process_flat_cloud(self, points, header):
        planes_info, remaining_indices = self.detect_planes_ransac(points)
        if not planes_info:
            return

        plane_indices = np.concatenate([p['inliers'] for p in planes_info])
        self.plane_cloud_pub.publish(self.numpy_to_pointcloud2(points[plane_indices], header))
        self.remaining_cloud_pub.publish(self.numpy_to_pointcloud2(points[remaining_indices], header))

        if self.publish_object_candidates:
            object_indices = self.extract_object_candidate_indices(points, planes_info[0])
            self.object_candidate_cloud_pub.publish(
                self.numpy_to_pointcloud2(points[object_indices], header)
            )

    def transform_xyz_only_cloud(self, msg, source_frame):
        xyz_cloud = self.make_xyz_only_cloud(msg)

        if not self.target_frame or self.target_frame == source_frame:
            return xyz_cloud

        try:
            transform = self.tf_buffer.lookup_transform(
                self.target_frame,
                source_frame,
                Time()
            )
            xyz_cloud.header.stamp = transform.header.stamp
            corrected_cloud = do_transform_cloud(xyz_cloud, transform)
            self.get_logger().debug(
                f"[plane_detector] Transformed cloud {source_frame} -> {self.target_frame}"
            )
            return corrected_cloud
        except Exception as e:
            self.get_logger().warn(f"TF lookup failed: {e}, using original XYZ-only cloud")
            return xyz_cloud

    def make_xyz_only_cloud(self, msg):
        """Strip RGB/padding fields before TF, matching the debug notebook path."""
        raw_points = point_cloud2.read_points(
            msg,
            field_names=("x", "y", "z"),
            skip_nans=False
        )
        raw_points = raw_points if isinstance(raw_points, np.ndarray) else np.asarray(list(raw_points))

        if raw_points.dtype.names:
            xyz_points = list(zip(raw_points['x'], raw_points['y'], raw_points['z']))
        else:
            xyz_points = [
                tuple(point)
                for point in np.asarray(raw_points, dtype=np.float32).reshape((-1, 3))
            ]

        return point_cloud2.create_cloud(
            msg.header,
            [
                PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
                PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
                PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1),
            ],
            xyz_points,
        )

    def pointcloud2_to_organized_xyz(self, cloud_msg, organized_height=None, organized_width=None):
        raw_points = point_cloud2.read_points(
            cloud_msg,
            field_names=("x", "y", "z"),
            skip_nans=False
        )
        points = raw_points if isinstance(raw_points, np.ndarray) else np.asarray(list(raw_points))

        if points.size == 0:
            return np.empty((0, 3), dtype=np.float32), np.empty((0,), dtype=bool)

        if points.dtype.names:
            points = np.stack(
                [points['x'], points['y'], points['z']],
                axis=-1
            )

        points = np.asarray(points, dtype=np.float32).reshape((-1, 3))
        height = organized_height if organized_height is not None else cloud_msg.height
        width = organized_width if organized_width is not None else cloud_msg.width

        if height > 1 and points.shape[0] == height * width:
            points = points.reshape((height, width, 3))

        valid = np.isfinite(points).all(axis=-1)
        return points, valid

    def select_table_plane(self, points, planes_info):
        """
        Pick the table the same way as the working notebook: in corrected z-up
        coordinates, prefer the highest mostly-horizontal plane. Students can
        inspect the notebook cells for the visual version of this logic.
        """
        scored_planes = []
        for plane in planes_info:
            model = np.asarray(plane['coefficients'], dtype=np.float32)
            normal = model[:3]
            normal_norm = np.linalg.norm(normal)
            if normal_norm < 1e-6:
                continue

            normal_unit = normal / normal_norm
            vertical_score = abs(float(normal_unit[2]))
            inliers = np.asarray(plane['inliers'], dtype=np.int64)
            median_z = float(np.nanmedian(points[inliers, 2])) if len(inliers) else -np.inf
            self.get_logger().info(
                f"[plane_detector] Plane candidate {plane.get('idx', '?')}: "
                f"vertical={vertical_score:.3f}, median_z={median_z:.3f}, inliers={len(inliers)}"
            )
            scored_planes.append((plane, vertical_score, median_z, len(inliers)))

        if not scored_planes:
            return planes_info[0]

        horizontal_planes = [
            item for item in scored_planes
            if item[1] >= self.table_normal_z_threshold
        ]
        elevated_horizontal_planes = [
            item for item in horizontal_planes
            if item[2] >= self.min_table_height
        ]

        if elevated_horizontal_planes:
            table_plane, vertical_score, median_z, inliers = max(
                elevated_horizontal_planes,
                key=lambda item: item[2]
            )
        elif horizontal_planes:
            table_plane, vertical_score, median_z, inliers = max(
                horizontal_planes,
                key=lambda item: item[2]
            )
        else:
            table_plane, vertical_score, median_z, inliers = max(
                scored_planes,
                key=lambda item: item[1] * item[3]
            )

        self.get_logger().info(
            f"[plane_detector] Selected table plane {table_plane.get('idx', '?')}: "
            f"vertical={vertical_score:.3f}, median_z={median_z:.3f}, inliers={inliers}"
        )

        return table_plane

    def extract_tabletop_objects(self, xyz, valid, valid_flat_indices, table_plane):
        """
        Notebook-style tabletop extraction:
        1. RANSAC table inliers become an image mask.
        2. Close/fill that mask to recover the tabletop region hidden by objects.
        3. Height-slice above the table.
        4. Black out everything outside the filled table region.
        5. Contour the remaining mask and return those organized-cloud points.

        See /home/oscar/Plane detector debug.ipynb for the teaching/debug version
        with plots after each step.
        """
        height, width = valid.shape
        flat_xyz = xyz.reshape((-1, 3))
        flat_valid = valid.reshape((-1,))

        plane_flat_indices = valid_flat_indices[np.asarray(table_plane['inliers'], dtype=np.int64)]
        plane_mask_flat = np.zeros(flat_xyz.shape[0], dtype=bool)
        plane_mask_flat[plane_flat_indices] = True
        plane_mask = plane_mask_flat.reshape((height, width))

        table_points = flat_xyz[plane_flat_indices]
        table_height_z = float(np.nanmedian(table_points[:, 2]))

        plane_u8 = (plane_mask.astype(np.uint8) * 255)
        table_region = self.make_filled_table_region(plane_u8)

        z_img = xyz[..., 2]
        height_above_table = z_img - table_height_z
        slice_mask_no_region = (
            valid
            & ~plane_mask
            & (height_above_table >= self.object_min_height)
            & (height_above_table <= self.object_max_height)
        )
        slice_mask = slice_mask_no_region & table_region

        self.get_logger().info(
            f"[plane_detector] Table mask pixels={int(plane_mask.sum())}, "
            f"filled_region_pixels={int(table_region.sum())}, "
            f"height_slice_pixels={int(slice_mask_no_region.sum())}, "
            f"inside_table_pixels={int(slice_mask.sum())}, "
            f"table_z={table_height_z:.3f}"
        )

        object_mask = self.clean_object_mask(slice_mask)
        contours, _ = cv2.findContours(
            object_mask,
            cv2.RETR_EXTERNAL,
            cv2.CHAIN_APPROX_SIMPLE
        )

        selected_mask = np.zeros_like(object_mask)
        kept_contours = 0
        objects = []
        for contour in contours:
            area = cv2.contourArea(contour)
            if not (self.min_contour_area <= area <= self.max_contour_area):
                continue

            contour_mask = np.zeros_like(object_mask)
            cv2.drawContours(contour_mask, [contour], -1, 255, thickness=-1)
            contour_pixels = (contour_mask > 0) & slice_mask
            contour_points = xyz[contour_pixels]
            contour_points = contour_points[np.isfinite(contour_points).all(axis=1)]
            if len(contour_points) == 0:
                continue

            x, y, w, h = cv2.boundingRect(contour)
            center_xyz = np.nanmedian(contour_points, axis=0)
            if not np.isfinite(center_xyz).all():
                continue

            cv2.drawContours(selected_mask, [contour], -1, 255, thickness=-1)
            objects.append({
                'id': kept_contours,
                'area_px': float(area),
                'bbox_px': (int(x), int(y), int(w), int(h)),
                'center_xyz': center_xyz.astype(np.float32),
                'points': int(len(contour_points)),
            })
            kept_contours += 1

        selected = (selected_mask > 0) & slice_mask
        object_indices = np.flatnonzero(selected.reshape((-1,)) & flat_valid)
        self.publish_tabletop_debug_image(
            xyz=xyz,
            valid=valid,
            plane_mask=plane_mask,
            table_region=table_region,
            slice_mask_no_region=slice_mask_no_region,
            slice_mask=slice_mask,
            object_mask=object_mask,
            selected_mask=selected_mask,
            objects=objects,
            table_plane=table_plane,
            table_height_z=table_height_z,
        )
        return object_indices.astype(np.int64), objects

    def publish_tabletop_debug_image(
        self,
        xyz,
        valid,
        plane_mask,
        table_region,
        slice_mask_no_region,
        slice_mask,
        object_mask,
        selected_mask,
        objects,
        table_plane,
        table_height_z,
    ):
        """
        Publish one overwrite-style debug mosaic for the service call.
        This mirrors the notebook stages: corrected z, RANSAC table mask,
        filled table support, height slice, gated slice, and final contours.
        """
        try:
            z_img = xyz[..., 2]
            z_panel = self.scalar_to_bgr(z_img, valid, cv2.COLORMAP_TURBO)
            selected_plane_overlay = z_panel.copy()
            selected_plane_overlay[plane_mask] = (0, 0, 255)

            if self.debug_stage == 'selected_plane':
                title = (
                    f"selected plane {table_plane.get('idx', '?')} "
                    f"pixels={int(plane_mask.sum())} z={table_height_z:.3f}"
                )
                debug = self.add_panel_title(title, selected_plane_overlay)
                msg = self.cv_bgr_to_imgmsg(debug)
                msg.header.stamp = self.get_clock().now().to_msg()
                msg.header.frame_id = self.target_frame
                self.debug_image_pub.publish(msg)
                return

            plane_panel = self.mask_to_bgr(plane_mask)
            table_panel = self.mask_to_bgr(table_region)
            raw_slice_panel = self.mask_to_bgr(slice_mask_no_region)
            gated_slice_panel = self.mask_to_bgr(slice_mask)
            contour_panel = cv2.cvtColor(object_mask, cv2.COLOR_GRAY2BGR)
            contour_panel[selected_mask > 0] = (0, 255, 0)

            for obj in objects:
                x, y, w, h = obj['bbox_px']
                cv2.rectangle(contour_panel, (x, y), (x + w, y + h), (0, 0, 255), 2)
                cv2.putText(
                    contour_panel,
                    str(obj['id']),
                    (x, max(15, y - 5)),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    (0, 0, 255),
                    1,
                    cv2.LINE_AA,
                )

            panels = [
                ('selected plane on z', selected_plane_overlay),
                ('selected plane mask', plane_panel),
                ('filled table roi', table_panel),
                ('height slice raw', raw_slice_panel),
                ('inside table', gated_slice_panel),
                ('final contours', contour_panel),
            ]

            titled = [self.add_panel_title(title, image) for title, image in panels]
            top = np.hstack(titled[:3])
            bottom = np.hstack(titled[3:])
            mosaic = np.vstack([top, bottom])

            msg = self.cv_bgr_to_imgmsg(mosaic)
            msg.header.stamp = self.get_clock().now().to_msg()
            msg.header.frame_id = self.target_frame
            self.debug_image_pub.publish(msg)
        except Exception as exc:
            self.get_logger().warn(f"[plane_detector] Could not publish tabletop debug image: {exc}")

    def scalar_to_bgr(self, image, valid, colormap):
        finite = np.isfinite(image) & valid
        out = np.zeros(image.shape, dtype=np.uint8)
        if np.any(finite):
            lo = np.nanpercentile(image[finite], 1)
            hi = np.nanpercentile(image[finite], 99)
            if hi > lo:
                scaled = (np.clip(image, lo, hi) - lo) / (hi - lo)
                out[finite] = (scaled[finite] * 255).astype(np.uint8)
        return cv2.applyColorMap(out, colormap)

    def mask_to_bgr(self, mask):
        return cv2.cvtColor((mask.astype(np.uint8) * 255), cv2.COLOR_GRAY2BGR)

    def add_panel_title(self, title, image):
        panel = image.copy()
        cv2.rectangle(panel, (0, 0), (panel.shape[1], 28), (0, 0, 0), thickness=-1)
        cv2.putText(
            panel,
            title,
            (8, 20),
            cv2.FONT_HERSHEY_SIMPLEX,
            0.55,
            (255, 255, 255),
            1,
            cv2.LINE_AA,
        )
        return panel

    def cv_bgr_to_imgmsg(self, image):
        msg = Image()
        msg.height = int(image.shape[0])
        msg.width = int(image.shape[1])
        msg.encoding = 'bgr8'
        msg.is_bigendian = False
        msg.step = int(image.shape[1] * 3)
        msg.data = image.tobytes()
        return msg

    def make_yolo_style_result(self, objects, header):
        """
        Return the same response fields as /yolo_detect. Downstream code can call
        /tabletop_detect with robotino_interfaces/YoloDetect and reuse the same
        class_names + poses + TF path. The class is intentionally generic:
        segmentation found an object candidate, not a semantic label.
        """
        detections = Detection2DArray()
        detections.header = header
        class_names = []
        poses = []
        now = self.get_clock().now().to_msg()

        for obj in objects:
            x, y, w, h = obj['bbox_px']

            detection = Detection2D()
            bbox = BoundingBox2D()
            bbox.center.position.x = float(x + w / 2.0)
            bbox.center.position.y = float(y + h / 2.0)
            bbox.size_x = float(w)
            bbox.size_y = float(h)
            detection.bbox = bbox

            hypothesis = ObjectHypothesisWithPose()
            hypothesis.hypothesis.class_id = "object"
            hypothesis.hypothesis.score = 1.0
            detection.results = [hypothesis]
            detections.detections.append(detection)

            pose = PoseStamped()
            pose.header.stamp = now
            pose.header.frame_id = header.frame_id
            pose.pose.position.x = float(obj['center_xyz'][0])
            pose.pose.position.y = float(obj['center_xyz'][1])
            pose.pose.position.z = float(obj['center_xyz'][2])
            pose.pose.orientation.x = 0.0
            pose.pose.orientation.y = 0.0
            pose.pose.orientation.z = 0.0
            pose.pose.orientation.w = 1.0
            poses.append(pose)
            class_names.append("object")

            self.get_logger().info(
                f"[plane_detector] object {obj['id']}: "
                f"bbox={obj['bbox_px']} points={obj['points']} "
                f"center=({pose.pose.position.x:.3f}, "
                f"{pose.pose.position.y:.3f}, {pose.pose.position.z:.3f})"
            )

        return {
            'detections': detections,
            'class_names': class_names,
            'poses': poses,
        }

    def make_filled_table_region(self, plane_u8):
        kernel_size = max(1, int(self.table_mask_kernel_size))
        if kernel_size % 2 == 0:
            kernel_size += 1

        kernel = np.ones((kernel_size, kernel_size), np.uint8)
        closed = cv2.morphologyEx(
            plane_u8,
            cv2.MORPH_CLOSE,
            kernel,
            iterations=max(1, int(self.table_mask_close_iterations))
        )

        expanded = cv2.dilate(
            closed,
            kernel,
            iterations=max(0, int(self.table_mask_dilate_iterations))
        )

        ys, xs = np.where(expanded > 0)
        if len(xs) < 3:
            return plane_u8 > 0

        # The selected table plane is often fragmented by objects and occlusion.
        # The notebook shows this visually: use all table-plane fragments to make
        # one image-space tabletop support, then black out everything outside it.
        hull_points = np.column_stack((xs, ys)).astype(np.int32)
        table_hull = cv2.convexHull(hull_points)

        table_region_u8 = np.zeros_like(plane_u8)
        cv2.drawContours(table_region_u8, [table_hull], -1, 255, thickness=-1)
        return table_region_u8 > 0

    def clean_object_mask(self, slice_mask):
        mask_u8 = (slice_mask.astype(np.uint8) * 255)
        kernel_size = max(1, int(self.object_mask_kernel_size))
        if kernel_size % 2 == 0:
            kernel_size += 1

        kernel = np.ones((kernel_size, kernel_size), np.uint8)
        clean_mask = cv2.morphologyEx(
            mask_u8,
            cv2.MORPH_OPEN,
            kernel,
            iterations=max(0, int(self.object_mask_open_iterations))
        )
        clean_mask = cv2.morphologyEx(
            clean_mask,
            cv2.MORPH_CLOSE,
            kernel,
            iterations=max(0, int(self.object_mask_close_iterations))
        )
        return clean_mask
    
    def detect_planes_ransac(self, points):
        """
        Detect planes using RANSAC via Open3D
        
        Returns:
            List of dicts with 'coefficients' and 'inliers' keys
        """
        try:
            planes_info = []
            remaining_points = points
            remaining_indices = np.arange(len(points), dtype=np.int64)
            
            iterations = 0
            
            while (
                len(remaining_points) >= self.min_plane_size
                and len(planes_info) < self.max_planes
            ):
                plane_model, inliers = self.segment_plane(remaining_points)

                if len(inliers) < self.min_plane_size:
                    self.get_logger().debug(
                        f"[plane_detector] RANSAC stopped: only {len(inliers)} inliers"
                    )
                    break
                
                [a, b, c, d] = plane_model
                inliers = np.asarray(inliers, dtype=np.int64)
                original_inliers = remaining_indices[inliers]
                
                # Check if it's a horizontal plane if required
                if self.horizontal_only:
                    # Horizontal plane has normal close to [0, 0, 1] or [0, 0, -1]
                    if abs(a) > self.normal_threshold or abs(b) > self.normal_threshold:
                        self.get_logger().debug(
                            f"[plane_detector] Skipping non-horizontal plane: "
                            f"normal=({a:.3f}, {b:.3f}, {c:.3f})"
                        )
                        keep_mask = np.ones(len(remaining_points), dtype=bool)
                        keep_mask[inliers] = False
                        remaining_points = remaining_points[keep_mask]
                        remaining_indices = remaining_indices[keep_mask]
                        iterations += 1
                        continue

                planes_info.append({
                    'idx': len(planes_info),
                    'coefficients': plane_model,
                    'inliers': original_inliers,
                    'normal': np.array([a, b, c]),
                    'distance': d
                })
                
                self.get_logger().info(
                    f"[plane_detector] Detected plane: normal=({a:.3f}, {b:.3f}, {c:.3f}), "
                    f"d={d:.3f}, inliers={len(inliers)}"
                )
                
                # Remove detected plane points for next iteration
                keep_mask = np.ones(len(remaining_points), dtype=bool)
                keep_mask[inliers] = False
                remaining_points = remaining_points[keep_mask]
                remaining_indices = remaining_indices[keep_mask]
                iterations += 1
            
            return planes_info, remaining_indices
            
        except Exception as e:
            self.get_logger().error(f"[plane_detector] RANSAC error: {e}", exc_info=True)
            return [], np.arange(len(points), dtype=np.int64)

    def extract_object_candidate_indices(self, points, table_plane):
        plane_model = np.asarray(table_plane['coefficients'], dtype=np.float32)
        normal = plane_model[:3]
        normal_norm = np.linalg.norm(normal)

        if normal_norm < 1e-6:
            return np.empty(0, dtype=np.int64)

        normal = normal / normal_norm
        d = float(plane_model[3] / normal_norm)

        # In sensor-frame use, objects on the table are normally on the camera side
        # of the fitted plane. Orient the normal so the camera origin is positive.
        if d < 0.0:
            normal = -normal
            d = -d

        signed_height = points @ normal + d
        table_mask = np.zeros(len(points), dtype=bool)
        table_mask[np.asarray(table_plane['inliers'], dtype=np.int64)] = True

        object_mask = (
            ~table_mask
            & np.isfinite(signed_height)
            & (signed_height >= self.object_min_height)
            & (signed_height <= self.object_max_height)
        )

        return np.flatnonzero(object_mask).astype(np.int64)

    def segment_plane(self, points):
        if O3D_AVAILABLE:
            pcd = o3d.geometry.PointCloud()
            pcd.points = o3d.utility.Vector3dVector(points)
            plane_model, inliers = pcd.segment_plane(
                distance_threshold=self.distance_threshold,
                ransac_n=self.ransac_n,
                num_iterations=self.num_iterations
            )
            return plane_model, np.asarray(inliers, dtype=np.int64)

        return self.segment_plane_numpy(points)

    def segment_plane_numpy(self, points):
        ransac_n = max(3, self.ransac_n)

        if len(points) < ransac_n:
            return [0.0, 0.0, 1.0, 0.0], np.empty(0, dtype=np.int64)

        if self.max_ransac_points > 0 and len(points) > self.max_ransac_points:
            sample_indices = self.rng.choice(
                len(points),
                size=self.max_ransac_points,
                replace=False
            )
            sample_points = points[sample_indices]
        else:
            sample_indices = np.arange(len(points), dtype=np.int64)
            sample_points = points

        best_model = [0.0, 0.0, 1.0, 0.0]
        best_inliers = np.empty(0, dtype=np.int64)

        for _ in range(self.num_iterations):
            candidate_ids = self.rng.choice(len(sample_points), size=ransac_n, replace=False)
            p1, p2, p3 = sample_points[candidate_ids[:3]]
            normal = np.cross(p2 - p1, p3 - p1)
            norm = np.linalg.norm(normal)

            if norm < 1e-6:
                continue

            normal = normal / norm
            d = -float(np.dot(normal, p1))
            distances = np.abs(sample_points @ normal + d)
            sample_inliers = np.flatnonzero(distances <= self.distance_threshold)

            if len(sample_inliers) > len(best_inliers):
                best_model = [float(normal[0]), float(normal[1]), float(normal[2]), d]
                best_inliers = sample_indices[sample_inliers]

        if len(best_inliers) == 0:
            return best_model, best_inliers

        normal = np.asarray(best_model[:3], dtype=np.float32)
        d = best_model[3]
        full_distances = np.abs(points @ normal + d)
        full_inliers = np.flatnonzero(full_distances <= self.distance_threshold)

        return best_model, full_inliers.astype(np.int64)

    def pointcloud2_to_xyz_array(self, cloud_msg):
        """Extract valid XYZ points from a PointCloud2 message."""
        raw_points = point_cloud2.read_points(
            cloud_msg,
            field_names=("x", "y", "z"),
            skip_nans=True
        )
        points = raw_points if isinstance(raw_points, np.ndarray) else list(raw_points)
        points = np.asarray(points)

        if points.size == 0:
            return np.empty((0, 3), dtype=np.float32)

        if points.dtype.names:
            points = np.stack(
                [points['x'], points['y'], points['z']],
                axis=-1
            )

        return points.reshape((-1, 3)).astype(np.float32)
    
    def numpy_to_pointcloud2(self, points, header):
        """
        Convert numpy array to PointCloud2 message
        
        Args:
            points: (N, 3) numpy array of xyz coordinates
            header: ROS header for the message
            
        Returns:
            PointCloud2 message
        """
        cloud = PointCloud2()
        cloud.header = header
        cloud.height = 1
        cloud.width = len(points)
        
        cloud.fields = [
            PointField(name='x', offset=0, datatype=PointField.FLOAT32, count=1),
            PointField(name='y', offset=4, datatype=PointField.FLOAT32, count=1),
            PointField(name='z', offset=8, datatype=PointField.FLOAT32, count=1),
        ]
        
        cloud.is_bigendian = False
        cloud.point_step = 12
        cloud.row_step = cloud.point_step * cloud.width
        cloud.is_dense = False
        
        # Pack points into bytes
        import struct
        flat = points.flatten().tolist()
        cloud.data = struct.pack('<' + 'f' * len(flat), *flat)
        
        return cloud


def main(args=None):
    rclpy.init(args=args)
    node = PlaneDetectorNode()
    
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        if rclpy.ok():
            rclpy.shutdown()


if __name__ == '__main__':
    main()
