from setuptools import find_packages
from setuptools import setup

setup(
    name='rto_msgs',
    version='0.0.0',
    packages=find_packages(
        include=('rto_msgs', 'rto_msgs.*')),
)
