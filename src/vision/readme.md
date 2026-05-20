
ros2 run vision vision_node --ros-args -p image_topic:=/kinect/rgb/image_raw

ros2 run vision yolo_server --ros-args -p image_topic:=/kinect/rgb/image_raw -p cloud_topic:=/kinect/depth/points

ros2 launch robotino_webots sim_teleop_joy.launch.py”


#########################


ros2 launch robotino_webots robotino_min.launch.py 

ros2 run vision vision_segment   --ros-args -p cloud_topic:=/kinect_sim/points


Open images, saved ( see code example in notebook )


