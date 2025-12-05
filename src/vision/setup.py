from setuptools import find_packages, setup
from glob import glob
import os

package_name = 'vision'

setup(
    name=package_name,
    version='0.0.0',
    packages=find_packages(exclude=['test']),
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),

        # --- Install launch files ---
        (os.path.join('share', package_name, 'launch'),
         glob('launch/*.launch.py')),

        # --- Install config files (optional, only if you create config/*.yaml) ---
        (os.path.join('share', package_name, 'config'),
         glob('config/*.yaml')),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='oscar',
    maintainer_email='ofc1227@tec.mx',
    description='Vision playground node (image + future point cloud)',
    license='TODO: License declaration',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
            'vision_node = vision.vision_node:main',
        ],
    },
)
