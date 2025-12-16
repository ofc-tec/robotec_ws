from setuptools import find_packages, setup

package_name = 'vision'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='oscar',
    maintainer_email='ofc1227@tec.mx',
    description='TODO: Package description',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'vision_node = vision.vision_node:main',  
            'yolo_server = vision.yolo_service_node:main',
            'kinect_pointcloud_node = vision.kinect_pointcloud_node:main',
             "face_recog_service_node = vision.face_recog_service_node:main",
        ],
    },
)
