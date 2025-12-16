#!/usr/bin/env python3
from __future__ import annotations

import json
from pathlib import Path
from typing import Dict, List, Optional, Tuple

import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image
from vision_msgs.msg import BoundingBox2D
from cv_bridge import CvBridge

from robotino_interfaces.srv import FaceRecog
from std_srvs.srv import Trigger
from example_interfaces.srv import SetBool

import numpy as np
import cv2

import torch
from ultralytics import YOLO
from facenet_pytorch import InceptionResnetV1

from ament_index_python.packages import get_package_share_directory
import os

def bbox2d_from_xyxy(x1: int, y1: int, x2: int, y2: int) -> BoundingBox2D:
    bb = BoundingBox2D()
    bb.center.position.x = float((x1 + x2) / 2.0)
    bb.center.position.y = float((y1 + y2) / 2.0)
    bb.size_x = float(max(0, x2 - x1))
    bb.size_y = float(max(0, y2 - y1))
    return bb


class FaceRecogServiceNode(Node):

    def __init__(self):
        super().__init__("face_recog_service_node")

        # --- Parameters ---
        self.declare_parameter("image_topic", "/kinect/rgb/image_raw")
        self.declare_parameter("debug_topic", "/vision/face_recog_debug_image")
        self.declare_parameter("db_dir", str(Path.home() / ".ros" / "face_db"))

        # Recognition threshold (L2 distance on embeddings)
        self.declare_parameter("distance_threshold", 0.95)

        # YOLO params
        vision_share = get_package_share_directory("vision")

                
        self.declare_parameter("model_path", "/home/oscar/robotino_ros2_ws/src/vision/config/yolov8n-face-lindevs.pt")
        #self.declare_parameter("model_path", "yolo8n-face.pt")   
        self.declare_parameter("min_confidence", 0.50)

        self.image_topic = self.get_parameter("image_topic").value
        self.debug_topic = self.get_parameter("debug_topic").value
        self.db_dir = Path(self.get_parameter("db_dir").value)

        self.distance_threshold = float(self.get_parameter("distance_threshold").value)
        self.min_confidence = float(self.get_parameter("min_confidence").value)
        self.model_path = str(self.get_parameter("model_path").value)

        self.get_logger().info(f"[FACE] image_topic: {self.image_topic}")
        self.get_logger().info(f"[FACE] debug_topic: {self.debug_topic}")
        self.get_logger().info(f"[FACE] db_dir     : {self.db_dir}")
        self.get_logger().info(f"[FACE] model_path : {self.model_path}")

        # --- Device ---
        self.device = "cuda:0" if torch.cuda.is_available() else "cpu"
        self.get_logger().info(f"[FACE] torch device: {self.device}")

        # --- CvBridge ---
        self.bridge = CvBridge()

        # --- Image cache ---
        self.latest_image_msg: Optional[Image] = None

        # --- Face DB ---
        self.db_dir.mkdir(parents=True, exist_ok=True)
        self.db_file = self.db_dir / "faces.json"
        self.known: Dict[str, List[List[float]]] = {}
        self._load_db()

        # --- Models ---
        # YOLO face detector
        self.detector = YOLO(self.model_path)

        # Embedding model (FaceNet)
        self.embedder = InceptionResnetV1(pretrained="vggface2").eval()
        if self.device.startswith("cuda"):
            self.embedder = self.embedder.to(self.device)

        # --- ROS interfaces ---
        self.create_subscription(Image, self.image_topic, self._image_cb, 10)
        self.debug_pub = self.create_publisher(Image, self.debug_topic, 10)

        # Two services in same node
        self.srv_recog = self.create_service(FaceRecog, "/face_recog", self._handle_face_recog)
        self.srv_train = self.create_service(FaceRecog, "/face_train", self._handle_face_train)

        # Optional DB helpers
        self.create_service(Trigger, "/face_db/list", self._handle_list)
        self.create_service(Trigger, "/face_db/save", self._handle_save)
        self.create_service(SetBool, "/face_db/forget_all", self._handle_forget_all)

        self.get_logger().info("[FACE] Ready (YOLO + FaceNet).")

    def _image_cb(self, msg: Image):
        self.latest_image_msg = msg

    # --------------------------
    # DB
    # --------------------------
    def _load_db(self):
        if not self.db_file.exists():
            return
        try:
            data = json.loads(self.db_file.read_text())
            self.known = data.get("known", {})
            self.get_logger().info(f"[FACE] Loaded {len(self.known)} identities.")
        except Exception as e:
            self.get_logger().warn(f"[FACE] DB load failed: {e}")

    def _save_db(self):
        tmp = self.db_file.with_suffix(".tmp")
        tmp.write_text(json.dumps({"known": self.known}))
        tmp.replace(self.db_file)

    # --------------------------
    # Vision
    # --------------------------
    def _get_latest_bgr(self) -> Optional[np.ndarray]:
        if self.latest_image_msg is None:
            return None
        return self.bridge.imgmsg_to_cv2(self.latest_image_msg, desired_encoding="bgr8")

    def _detect_faces_yolo(self, bgr: np.ndarray) -> List[Tuple[int,int,int,int,float]]:
        # Ultralytics expects RGB
        rgb = cv2.cvtColor(bgr, cv2.COLOR_BGR2RGB)

        # Predict
        results = self.detector.predict(
            source=rgb,
            device=0 if self.device.startswith("cuda") else "cpu",
            conf=self.min_confidence,
            verbose=False
        )

        dets: List[Tuple[int,int,int,int,float]] = []
        if not results:
            return dets

        r = results[0]
        if r.boxes is None or len(r.boxes) == 0:
            return dets

        h, w = bgr.shape[:2]
        xyxy = r.boxes.xyxy.detach().cpu().numpy()
        conf = r.boxes.conf.detach().cpu().numpy()

        for (x1, y1, x2, y2), c in zip(xyxy, conf):
            x1i = int(max(0, min(w-1, round(x1))))
            y1i = int(max(0, min(h-1, round(y1))))
            x2i = int(max(0, min(w-1, round(x2))))
            y2i = int(max(0, min(h-1, round(y2))))
            if x2i <= x1i or y2i <= y1i:
                continue
            dets.append((x1i, y1i, x2i, y2i, float(c)))

        return dets

    def _embed_face(self, bgr: np.ndarray, box: Tuple[int,int,int,int]) -> np.ndarray:
        x1,y1,x2,y2 = box
        crop = bgr[y1:y2, x1:x2]

        # FaceNet expects RGB, 160x160, float tensor normalized
        rgb = cv2.cvtColor(crop, cv2.COLOR_BGR2RGB)
        rgb = cv2.resize(rgb, (160, 160), interpolation=cv2.INTER_LINEAR)
        t = torch.from_numpy(rgb).float() / 255.0              # [H,W,C]
        t = t.permute(2,0,1).unsqueeze(0)                     # [1,3,160,160]
        t = (t - 0.5) / 0.5                                   # normalize to [-1,1]

        if self.device.startswith("cuda"):
            t = t.to(self.device)

        with torch.no_grad():
            emb = self.embedder(t).detach().cpu().numpy()[0]  # [512]
        # L2 normalize
        emb = emb / (np.linalg.norm(emb) + 1e-9)
        return emb

    def _best_match(self, enc: np.ndarray) -> Tuple[str, float]:
        best_name = "unknown"
        best_dist = 1e9
        for name, samples in self.known.items():
            for s in samples:
                v = np.array(s, dtype=np.float32)
                # L2 distance on normalized embeddings
                d = float(np.linalg.norm(enc - v))
                if d < best_dist:
                    best_dist = d
                    best_name = name
        return best_name, best_dist

    def _dist_to_conf(self, dist: float) -> float:
        # simple mapping: 0 dist -> 1.0, threshold -> ~0.0
        return max(0.0, min(1.0, 1.0 - dist / self.distance_threshold))

    # --------------------------
    # Services
    # --------------------------
    def _handle_face_recog(self, req, res):
        bgr = self._get_latest_bgr()
        if bgr is None:
            return res

        dets = self._detect_faces_yolo(bgr)
        debug_items = []

        if not dets:
            self._publish_debug(bgr, [])
            return res

        for (x1,y1,x2,y2,det_conf) in dets:
            emb = self._embed_face(bgr, (x1,y1,x2,y2))
            name, dist = self._best_match(emb)
            conf = self._dist_to_conf(dist)

            if dist > self.distance_threshold:
                name = "unknown"

            res.name_response.append(name)
            res.confidence.append(conf)
            res.features.append("ok")
            res.bounding_boxes.append(bbox2d_from_xyxy(x1,y1,x2,y2))

            # debug shows ALL faces, including unknown
            debug_items.append((x1,y1,x2,y2,name,conf,det_conf))

        self._publish_debug(bgr, debug_items)
        return res

    def _handle_face_train(self, req, res):
        bgr = self._get_latest_bgr()
        if bgr is None:
            return res

        # Accept either req.train_name OR req.name (depends on your srv)
        train_name = ""
        if hasattr(req, "train_name"):
            train_name = (req.train_name or "").strip()
        elif hasattr(req, "name"):
            train_name = (req.name or "").strip()

        if not train_name:
            # no training requested
            return res

        dets = self._detect_faces_yolo(bgr)
        if not dets:
            self._publish_debug(bgr, [])
            return res

        # pick largest face
        dets_sorted = sorted(dets, key=lambda d: (d[2]-d[0])*(d[3]-d[1]), reverse=True)
        x1,y1,x2,y2,det_conf = dets_sorted[0]

        emb = self._embed_face(bgr, (x1,y1,x2,y2))

        self.known.setdefault(train_name, [])
        self.known[train_name].append(emb.astype(float).tolist())
        self._save_db()

        # return one bbox + name for visibility
        res.name_response.append(train_name)
        res.confidence.append(1.0)
        res.features.append("trained")
        res.bounding_boxes.append(bbox2d_from_xyxy(x1,y1,x2,y2))

        self._publish_debug(bgr, [(x1,y1,x2,y2,train_name,1.0,det_conf)])
        return res

    # --------------------------
    # Debug
    # --------------------------
    def _publish_debug(self, bgr: np.ndarray, items):
        dbg = bgr.copy()

        for it in items:
            # accept both 6-tuple and 7-tuple
            if len(it) == 7:
                x1,y1,x2,y2,name,conf,det_conf = it
                label = f"{name} {conf:.2f} det:{det_conf:.2f}"
            else:
                x1,y1,x2,y2,name,conf = it
                label = f"{name} {conf:.2f}"

            cv2.rectangle(dbg, (x1,y1), (x2,y2), (0,255,0), 2)
            cv2.putText(dbg, label, (x1, max(0,y1-6)),
                        cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0,255,0), 1, cv2.LINE_AA)

        msg = self.bridge.cv2_to_imgmsg(dbg, encoding="bgr8")
        if self.latest_image_msg is not None:
            msg.header = self.latest_image_msg.header
        self.debug_pub.publish(msg)

    # --------------------------
    # DB helpers
    # --------------------------
    def _handle_list(self, req, res):
        res.success = True
        res.message = ", ".join(sorted(self.known.keys()))
        return res

    def _handle_save(self, req, res):
        self._save_db()
        res.success = True
        res.message = "saved"
        return res

    def _handle_forget_all(self, req, res):
        if req.data:
            self.known = {}
            self._save_db()
            res.success = True
            res.message = "cleared"
        else:
            res.success = True
            res.message = "noop"
        return res


def main():
    rclpy.init()
    node = FaceRecogServiceNode()
    try:
        rclpy.spin(node)
    except KeyboardInterrupt:
        pass
    finally:
        node.destroy_node()
        rclpy.shutdown()


if __name__ == "__main__":
    main()
