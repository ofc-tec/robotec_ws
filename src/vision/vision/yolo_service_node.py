#!/usr/bin/env python3
"""
YOLO Detect Service (ROS 2) — corrected drop-in version

Key behavior:
- ALWAYS returns 2D detections + class_names.
- Returns 3D PoseStamped ONLY when depth is valid:
    pose.header.frame_id = parent_frame (typically your depth frame)
    pose.pose.position = (cx3, cy3, cz3) in that frame
- DOES NOT depend on map / base_link / localization.
- DOES NOT do any TF lookups to map.
- Publishes TF frames yolo_<class>_<i> as child of parent_frame (sensor frame).
"""

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image, CameraInfo
from vision_msgs.msg import Detection2DArray, Detection2D, ObjectHypothesisWithPose, BoundingBox2D
from robotino_interfaces.srv import YoloDetect

from cv_bridge import CvBridge
from ultralytics import YOLO

import cv2
import numpy as np
import re
import tf2_ros
from geometry_msgs.msg import TransformStamped, PoseStamped


class YoloServiceNode(Node):
    def __init__(self):
        super().__init__("yolo_service_node")

        self.bridge = CvBridge()

        # --- Parameters ---
        self.declare_parameter("image_topic", "/kinect/rgb/image_raw")
        self.declare_parameter("depth_topic", "/kinect/depth/image_raw")
        self.declare_parameter("depth_info_topic", "/kinect/depth/camera_info")
        self.declare_parameter("model_path", "yolo11n-seg.pt")  # adjust as needed
        self.declare_parameter("confidence_threshold", 0.25)
        self.declare_parameter("yolo_input_color", "bgr")
        self.declare_parameter("log_image_stats", True)

        image_topic = self.get_parameter("image_topic").get_parameter_value().string_value
        depth_topic = self.get_parameter("depth_topic").get_parameter_value().string_value
        depth_info_topic = self.get_parameter("depth_info_topic").get_parameter_value().string_value
        model_path = self.get_parameter("model_path").get_parameter_value().string_value
        self.confidence_threshold = float(self.get_parameter("confidence_threshold").value)
        self.yolo_input_color = (
            self.get_parameter("yolo_input_color").get_parameter_value().string_value.lower()
        )
        self.log_image_stats = bool(self.get_parameter("log_image_stats").value)
        if self.yolo_input_color not in ("bgr", "rgb"):
            self.get_logger().warn(
                f"[YOLO_SERVICE] Invalid yolo_input_color={self.yolo_input_color!r}; using 'bgr'."
            )
            self.yolo_input_color = "bgr"

        self.get_logger().info(f"[YOLO_SERVICE] Using RGB topic        : {image_topic}")
        self.get_logger().info(f"[YOLO_SERVICE] Using DEPTH topic      : {depth_topic}")
        self.get_logger().info(f"[YOLO_SERVICE] Using DEPTH info topic : {depth_info_topic}")
        self.get_logger().info(f"[YOLO_SERVICE] Using model            : {model_path}")
        self.get_logger().info(f"[YOLO_SERVICE] Confidence threshold  : {self.confidence_threshold:.3f}")
        self.get_logger().info(f"[YOLO_SERVICE] YOLO input color order : {self.yolo_input_color.upper()}")
        self.get_logger().info("[YOLO_SERVICE] Output poses are in SENSOR frame only (no map/base).")

        # --- Subscriptions ---
        self.latest_image_msg = None
        self.latest_depth_msg = None
        self.latest_cam_info = None

        self.image_sub = self.create_subscription(Image, image_topic, self.image_callback, 10)
        self.depth_sub = self.create_subscription(Image, depth_topic, self.depth_callback, 10)
        self.cam_info_sub = self.create_subscription(CameraInfo, depth_info_topic, self.cam_info_callback, 10)

        # --- TF broadcaster (publishes yolo_<class>_<i> under parent_frame) ---
        self.tf_broadcaster = tf2_ros.TransformBroadcaster(self)

        # --- Debug image publisher ---
        self.debug_pub = self.create_publisher(Image, "/vision/yolo_debug_image", 10)

        # --- YOLO seg model ---
        self.model = YOLO(model_path)
        self.class_names = self.model.names  # dict: id -> name

        # --- Service server ---
        self.srv = self.create_service(YoloDetect, "/yolo_detect", self.handle_yolo_detect)

        self.get_logger().info("[YOLO_SERVICE] Ready (depth optional: 2D always, 3D+TF only when depth OK).")

    # ==========================
    # Callbacks
    # ==========================
    def image_callback(self, msg: Image):
        self.latest_image_msg = msg

    def depth_callback(self, msg: Image):
        self.latest_depth_msg = msg

    def cam_info_callback(self, msg: CameraInfo):
        self.latest_cam_info = msg

    def _log_rgb_image_stats(self, frame_bgr):
        means = frame_bgr.reshape(-1, 3).mean(axis=0)
        center = frame_bgr[frame_bgr.shape[0] // 2, frame_bgr.shape[1] // 2].tolist()
        self.get_logger().info(
            "[YOLO_SERVICE] RGB msg "
            f"encoding={self.latest_image_msg.encoding} "
            f"frame_id={self.latest_image_msg.header.frame_id!r} "
            f"shape={frame_bgr.shape} "
            f"BGR_mean=({means[0]:.1f}, {means[1]:.1f}, {means[2]:.1f}) "
            f"center_BGR={center}"
        )

    def _log_detections(self, boxes_xyxy, class_ids, confidences):
        if len(confidences) == 0:
            self.get_logger().info(
                f"[YOLO_SERVICE] YOLO candidates above conf={self.confidence_threshold:.3f}: none"
            )
            return

        order = np.argsort(-confidences)
        parts = []
        for idx in order[:20]:
            x1, y1, x2, y2 = boxes_xyxy[idx]
            class_name = self.class_names.get(int(class_ids[idx]), "obj")
            parts.append(
                f"{class_name}:{confidences[idx]:.3f}"
                f" bbox=({int(x1)},{int(y1)},{int(x2)},{int(y2)})"
            )

        extra = "" if len(confidences) <= 20 else f" ... +{len(confidences) - 20} more"
        self.get_logger().info(
            f"[YOLO_SERVICE] YOLO candidates above conf={self.confidence_threshold:.3f}: "
            + "; ".join(parts)
            + extra
        )

    def _safe_tf_name(self, name):
        safe = re.sub(r"[^A-Za-z0-9_]", "_", str(name)).strip("_")
        return safe or "obj"

    def _pose_from_depth_pixels(self, X, Y, Z, ys_full, xs_full):
        if len(xs_full) == 0 or len(ys_full) == 0:
            return None

        X_pts = X[ys_full, xs_full]
        Y_pts = Y[ys_full, xs_full]
        Z_pts = Z[ys_full, xs_full]
        good = np.isfinite(X_pts) & np.isfinite(Y_pts) & np.isfinite(Z_pts)
        if not np.any(good):
            return None

        cx3 = float(np.nanmedian(X_pts[good]))
        cy3 = float(np.nanmedian(Y_pts[good]))
        cz3 = float(np.nanmedian(Z_pts[good]))
        if not (np.isfinite(cx3) and np.isfinite(cy3) and np.isfinite(cz3)):
            return None

        return cx3, cy3, cz3

    def _publish_yolo_tf(self, parent_frame, child_frame_id, now, xyz):
        cx3, cy3, cz3 = xyz

        t = TransformStamped()
        t.header.stamp = now
        t.header.frame_id = parent_frame
        t.child_frame_id = child_frame_id
        t.transform.translation.x = cx3
        t.transform.translation.y = cy3
        t.transform.translation.z = cz3
        t.transform.rotation.x = 0.0
        t.transform.rotation.y = 0.0
        t.transform.rotation.z = 0.0
        t.transform.rotation.w = 1.0
        self.tf_broadcaster.sendTransform(t)

        pose_out = PoseStamped()
        pose_out.header.stamp = now
        pose_out.header.frame_id = parent_frame
        pose_out.pose.position.x = cx3
        pose_out.pose.position.y = cy3
        pose_out.pose.position.z = cz3
        pose_out.pose.orientation.x = 0.0
        pose_out.pose.orientation.y = 0.0
        pose_out.pose.orientation.z = 0.0
        pose_out.pose.orientation.w = 1.0
        return pose_out

    # ==========================
    # Service handler
    # ==========================
    def handle_yolo_detect(self, request, response: YoloDetect.Response):
        # Always initialize
        response.class_names = []
        response.poses = []
        response.detections = Detection2DArray()

        if self.latest_image_msg is None:
            self.get_logger().warn("[YOLO_SERVICE] No RGB image yet.")
            return response

        # --- RGB image ---
        frame_bgr = self.bridge.imgmsg_to_cv2(self.latest_image_msg, desired_encoding="bgr8")
        H_img, W_img, _ = frame_bgr.shape
        if self.log_image_stats:
            self._log_rgb_image_stats(frame_bgr)

        # Prepare detections msg header
        detections_msg = Detection2DArray()
        detections_msg.header = self.latest_image_msg.header

        # --------------------------
        # Depth is OPTIONAL
        # --------------------------
        depth_ok = (self.latest_depth_msg is not None)
        if not depth_ok:
            self.get_logger().warn("[YOLO_SERVICE] No depth image yet. Returning 2D only (poses invalid).")

        X = Y = Z = None  # 3D arrays only if depth_ok
        parent_frame = "kinect_depth"
        if self.latest_depth_msg is not None and self.latest_depth_msg.header.frame_id:
            parent_frame = self.latest_depth_msg.header.frame_id

        if depth_ok:
            try:
                depth = self.bridge.imgmsg_to_cv2(self.latest_depth_msg, desired_encoding="passthrough")
                self.get_logger().info(
                    f"[YOLO_SERVICE] depth encoding={self.latest_depth_msg.encoding}, shape={depth.shape}"
                )
            except Exception as e:
                self.get_logger().warn(f"[YOLO_SERVICE] cv_bridge depth error: {e}")
                depth_ok = False

        if depth_ok:
            if depth.ndim == 3 and depth.shape[2] == 1:
                depth = depth[:, :, 0]
            if depth.ndim != 2:
                self.get_logger().warn(
                    f"[YOLO_SERVICE] Depth image is not single-channel "
                    f"(encoding={self.latest_depth_msg.encoding}, shape={depth.shape}). Returning 2D only."
                )
                depth_ok = False

        if depth_ok:
            H_d, W_d = depth.shape
            if H_d != H_img or W_d != W_img:
                self.get_logger().info(
                    f"[YOLO_SERVICE] Depth size ({H_d},{W_d}) differs from RGB size ({H_img},{W_img}); "
                    "scaling mask pixels into depth image."
                )

        if depth_ok:
            # Prefer the depth CameraInfo intrinsics. Fall back to Kinect-ish defaults.
            fx = 525.0
            fy = 525.0
            cx = 319.5
            cy = 239.5
            if self.latest_cam_info is not None and len(self.latest_cam_info.k) >= 6:
                k = self.latest_cam_info.k
                if k[0] > 0.0 and k[4] > 0.0:
                    fx = float(k[0])
                    fy = float(k[4])
                    cx = float(k[2])
                    cy = float(k[5])
                else:
                    self.get_logger().warn("[YOLO_SERVICE] Depth CameraInfo has invalid K; using fallback intrinsics.")
            else:
                self.get_logger().warn("[YOLO_SERVICE] No depth CameraInfo yet; using fallback intrinsics.")

            # --- Depth units ---
            if self.latest_depth_msg.encoding == "16UC1":
                Z = depth.astype(np.float32) / 1000.0  # mm -> m
            else:
                Z = depth.astype(np.float32)

            # Sanitize + clamp
            Z[~np.isfinite(Z)] = np.nan
            Z[Z <= 0.0] = np.nan
            Z[(Z < 0.25) | (Z > 6.0)] = np.nan

            # Back-project to 3D in the depth frame convention used by your projection
            u = np.tile(np.arange(W_d), (H_d, 1))
            v = np.tile(np.arange(H_d).reshape(-1, 1), (1, W_d))

            X = (u - cx) * Z / fx
            Y = (v - cy) * Z / fy

        # --- YOLO segmentation ---
        yolo_frame = frame_bgr
        if self.yolo_input_color == "rgb":
            yolo_frame = cv2.cvtColor(frame_bgr, cv2.COLOR_BGR2RGB)
        results = self.model.predict(
            source=yolo_frame,
            conf=self.confidence_threshold,
            verbose=False,
        )
        result = results[0]

        boxes = result.boxes
        masks = result.masks

        if boxes is None or len(boxes) == 0:
            self.get_logger().info("[YOLO_SERVICE] No detections.")
            annotated = result.plot()
            debug_msg = self.bridge.cv2_to_imgmsg(annotated, encoding="bgr8")
            debug_msg.header = self.latest_image_msg.header
            self.debug_pub.publish(debug_msg)

            response.detections = detections_msg
            return response

        boxes_xyxy = boxes.xyxy.cpu().numpy()
        class_ids = boxes.cls.cpu().numpy().astype(int)
        confidences = boxes.conf.cpu().numpy()
        self._log_detections(boxes_xyxy, class_ids, confidences)

        # Debug image
        annotated = result.plot()
        debug_msg = self.bridge.cv2_to_imgmsg(annotated, encoding="bgr8")
        debug_msg.header = self.latest_image_msg.header
        self.debug_pub.publish(debug_msg)

        # Masks
        mask_array = None
        if masks is not None and masks.data is not None:
            mask_array = masks.data.cpu().numpy()  # [N, H, W]
            if mask_array.shape[1] != H_img or mask_array.shape[2] != W_img:
                self.get_logger().info(
                    f"[YOLO_SERVICE] Resizing mask size {mask_array.shape[1:]} to image size {(H_img, W_img)}."
                )
                resized_masks = []
                for mask in mask_array:
                    resized_masks.append(
                        cv2.resize(mask, (W_img, H_img), interpolation=cv2.INTER_NEAREST)
                    )
                mask_array = np.stack(resized_masks, axis=0)

        now = self.get_clock().now().to_msg()

        # ==========================
        # Loop detections (2D always)
        # ==========================
        for i, box in enumerate(boxes_xyxy):
            detection = Detection2D()

            x1, y1, x2, y2 = box
            x1_i = max(0, min(W_img - 1, int(x1)))
            x2_i = max(0, min(W_img - 1, int(x2)))
            y1_i = max(0, min(H_img - 1, int(y1)))
            y2_i = max(0, min(H_img - 1, int(y2)))

            # 2D bbox
            bbox = BoundingBox2D()
            bbox.center.position.x = float((x1_i + x2_i) / 2.0)
            bbox.center.position.y = float((y1_i + y2_i) / 2.0)
            bbox.size_x = float(x2_i - x1_i)
            bbox.size_y = float(y2_i - y1_i)
            detection.bbox = bbox

            # hypothesis
            hypothesis = ObjectHypothesisWithPose()
            hypothesis.hypothesis.class_id = str(class_ids[i])
            hypothesis.hypothesis.score = float(confidences[i])
            detection.results = [hypothesis]

            detections_msg.detections.append(detection)

            # class name aligned with detections
            class_name = self.class_names.get(class_ids[i], "obj")
            response.class_names.append(class_name)

            # Default pose entry: invalid (no 3D)
            pose_out = PoseStamped()
            pose_out.header.frame_id = ""  # invalid unless we set 3D below

            child_frame_id = f"yolo_{self._safe_tf_name(class_name)}_{i}"

            if depth_ok and (X is not None) and (Y is not None) and (Z is not None):
                x1_d = max(0, min(W_d - 1, int(round(x1_i * W_d / W_img))))
                x2_d = max(0, min(W_d - 1, int(round(x2_i * W_d / W_img))))
                y1_d = max(0, min(H_d - 1, int(round(y1_i * H_d / H_img))))
                y2_d = max(0, min(H_d - 1, int(round(y2_i * H_d / H_img))))

                if x2_d <= x1_d or y2_d <= y1_d:
                    self.get_logger().warn(
                        f"[YOLO_SERVICE] No TF for {child_frame_id}: empty depth bbox "
                        f"({x1_d},{y1_d})-({x2_d},{y2_d})."
                    )
                else:
                    xyz = None
                    tf_source = "mask"

                    if mask_array is not None and i < mask_array.shape[0]:
                        mask = mask_array[i]
                        if mask.shape != Z.shape:
                            mask = cv2.resize(mask, (W_d, H_d), interpolation=cv2.INTER_NEAREST)

                        submask = mask[y1_d:y2_d, x1_d:x2_d] > 0.5
                        if np.any(submask):
                            ys_idx, xs_idx = np.where(submask)
                            ys_full = ys_idx + y1_d
                            xs_full = xs_idx + x1_d
                            xyz = self._pose_from_depth_pixels(X, Y, Z, ys_full, xs_full)

                    if xyz is None:
                        tf_source = "bbox"
                        crop_z = Z[y1_d:y2_d, x1_d:x2_d]
                        good = np.isfinite(crop_z)
                        if np.any(good):
                            ys_idx, xs_idx = np.where(good)
                            ys_full = ys_idx + y1_d
                            xs_full = xs_idx + x1_d
                            xyz = self._pose_from_depth_pixels(X, Y, Z, ys_full, xs_full)

                    if xyz is not None:
                        pose_out = self._publish_yolo_tf(parent_frame, child_frame_id, now, xyz)
                        self.get_logger().info(
                            f"[YOLO_SERVICE] TF {parent_frame}->{child_frame_id} "
                            f"from {tf_source}: ({xyz[0]:.3f}, {xyz[1]:.3f}, {xyz[2]:.3f})"
                        )
                    else:
                        self.get_logger().warn(
                            f"[YOLO_SERVICE] No TF for {child_frame_id}: no valid depth in mask/bbox."
                        )
            else:
                self.get_logger().warn(
                    f"[YOLO_SERVICE] No TF for {child_frame_id}: depth_ok={depth_ok}, "
                    f"X/Y/Z ready={X is not None and Y is not None and Z is not None}."
                )

            response.poses.append(pose_out)

        response.detections = detections_msg
        self.get_logger().info(
            f"[YOLO_SERVICE] Request handled: {len(detections_msg.detections)} detections, "
            f"3D={'yes' if depth_ok else 'no'} (poses valid only when 3D), "
            f"class_names={len(response.class_names)} poses={len(response.poses)}"
        )
        return response


def main(args=None):
    rclpy.init(args=args)
    node = YoloServiceNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
