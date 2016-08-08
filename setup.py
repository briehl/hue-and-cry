from distutils.core import setup
from hueandcry import __version__
import os

def read(fname):
    return open(os.path.join(os.path.dirname(__file__), fname)).read()

setup(
    name='hueandcry',
    version=__version__,
    author='Bill Riehl',
    install_requires=[s.strip() for s in open("requirements.txt")],
    packages=['hueandcry'],
    url='https://github.com/briehl/hue-and-cry',
    license='MIT',
    description='A pretty simple library for controlling Philips Hue lights.',
    long_description=read('README.md'),
    classifiers=[
        'Development Status :: 1 - Planning',
        'Environment :: Console',
        'License :: OSI Approved :: MIT License',
        'Operating System :: OS Independent',
        'Topic :: Home Automation'
    ]
)