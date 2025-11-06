from setuptools import find_packages
from setuptools import setup

setup(
    name='rto_node',
    version='0.0.0',
    packages=find_packages(
        include=('rto_node', 'rto_node.*')),
)
