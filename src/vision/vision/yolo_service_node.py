import rclpy
from rclpy.node import Node

from sensor_msgs.msg import Image
from cv_bridge import CvBridge

from robotino_interfaces.srv import YoloDetect
from vision_msgs.msg import Detection2DArray, Detection2D, BoundingBox2D, ObjectHypothesisWithPose

from ultralytics import YOLO   # make sure ultralytics is installed in your venv
import torch
import numpy as np


class YoloServiceNode(Node):
    def __init__(self):
        super().__init__('yolo_service_node')

        # --- Bridge & state ---
        self.bridge = CvBridge()
        self.latest_image_msg = None

        # --- Parameters ---
        self.declare_parameter('image_topic', '/camera/image_raw')
        self.declare_parameter('model_path', 'yolo11n.pt')
        #self.declare_parameter('model_path', 'yolo11n-seg.pt')

        image_topic = self.get_parameter('image_topic').get_parameter_value().string_value
        model_path = self.get_parameter('model_path').get_parameter_value().string_value

        # --- Load YOLO model once ---
        self.get_logger().info(f'[YOLO_SERVICE] Loading YOLO model: {model_path}')
        self.model = YOLO(model_path)

        self.get_logger().info('[YOLO_SERVICE] Model loaded.')

        # --- Camera subscriber (store last image) ---
        self.image_sub = self.create_subscription(
            Image,
            image_topic,
            self.image_callback,
            10
        )

        # --- Debug image publisher (annotated image with boxes/masks) ---
        self.debug_pub = self.create_publisher(
            Image,
            '/yolo_debug_image',
            10
        )

        # --- Service server ---
        self.srv = self.create_service(
            YoloDetect,
            'yolo_detect',   # service name: /yolo_detect
            self.handle_yolo_detect
        )

        self.get_logger().info(
            f'[YOLO_SERVICE] Node ready, subscribed to {image_topic}, waiting for /yolo_detect requests...'
        )

    # --------------------------------------------------------------------- #
    # Callbacks                                                             #
    # --------------------------------------------------------------------- #

    def image_callback(self, msg: Image):
        """Store the last received image."""
        self.latest_image_msg = msg

    def handle_yolo_detect(self, request, response):
        """Service callback for /yolo_detect."""
        if self.latest_image_msg is None:
            self.get_logger().warn('[YOLO_SERVICE] No image received yet.')
            response.detections = Detection2DArray()
            return response

        # --- 1) ROS Image -> OpenCV (BGR) ---
        try:
            cv_image = self.bridge.imgmsg_to_cv2(
                self.latest_image_msg,
                desired_encoding='bgr8'
            )
        except Exception as e:
            self.get_logger().error(f'[YOLO_SERVICE] cv_bridge error: {e}')
            response.detections = Detection2DArray()
            return response

        # YOLO usually expects RGB; depends on how you trained / use it
        rgb_image = cv_image[:, :, ::-1]

        # --- 2) Run YOLO (no gradients needed) ---
        with torch.no_grad():
            results = self.model(rgb_image)#, conf=0.01)

        if not results:
            self.get_logger().warn('[YOLO_SERVICE] YOLO returned no results.')
            detections_msg = Detection2DArray()
            detections_msg.header = self.latest_image_msg.header
            response.detections = detections_msg
            return response

        result = results[0]

        # --- Extract boxes from YOLO results ---
        boxes = result.boxes
        boxes_np = None
        confidences = None
        class_ids = None

        if boxes is not None:
            boxes_np = boxes.xyxy.cpu().numpy()
            confidences = boxes.conf.cpu().numpy()
            class_ids = boxes.cls.cpu().numpy().astype(int)
            
            num_detections = len(boxes_np)
            self.get_logger().info(f'✅ Found {num_detections} detections')
            
            # Log each detection
            for i in range(num_detections):
                cls_name = result.names[int(class_ids[i])]
                conf = confidences[i]
                box = boxes_np[i]
                self.get_logger().info(f'   Box {i}: {cls_name} ({conf:.2f}) at {box}')
        else:
            self.get_logger().warn('⚠️ No boxes in results')

        # --- 3) Publish debug image with boxes/masks overlaid ---
        # result.plot() returns an annotated image (numpy array, BGR)
        annotated = result.plot()
        debug_msg = self.bridge.cv2_to_imgmsg(annotated, encoding='rgb8')
        debug_msg.header = self.latest_image_msg.header
        self.debug_pub.publish(debug_msg)
        
        
        # --- 3) Publish debug image with boxes/masks overlaid ---
        #try:
        #    # result.plot() returns an annotated image (numpy array, BGR)
        #    annotated = result.plot()
        #    debug_msg = self.bridge.cv2_to_imgmsg(annotated, encoding='bgr8')
        #    debug_msg.header = self.latest_image_msg.header
        #    self.debug_pub.publish(debug_msg)
        #except Exception as e:
        #    self.get_logger().warn(f'[YOLO_SERVICE] Failed to publish debug image: {e}')
            
        # --- 4) Detection2DArray response ---
        detections_msg = Detection2DArray()
        detections_msg.header = self.latest_image_msg.header

        # Fill detections_msg.detections with Detection2D entries
        if boxes_np is not None and len(boxes_np) > 0:
            for i in range(len(boxes_np)):
                detection = Detection2D()
                
                # Set bounding box (convert from [x1, y1, x2, y2] to [center_x, center_y, width, height])
                x1, y1, x2, y2 = boxes_np[i]
                bbox = BoundingBox2D()
                bbox.center.position.x = float((x1 + x2) / 2.0)
                bbox.center.position.y = float((y1 + y2) / 2.0)
                bbox.size_x = float(x2 - x1)
                bbox.size_y = float(y2 - y1)
                detection.bbox = bbox
                
                # Set hypothesis (class and confidence)
                hypothesis = ObjectHypothesisWithPose()
                hypothesis.hypothesis.class_id = str(class_ids[i])
                hypothesis.hypothesis.score = float(confidences[i])
                detection.results = [hypothesis]
                
                detections_msg.detections.append(detection)

        response.detections = detections_msg

        self.get_logger().info(
            f'[YOLO_SERVICE] Request handled (debug image published, {len(detections_msg.detections)} detections).'
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


if __name__ == '__main__':
    main()