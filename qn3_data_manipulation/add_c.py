from setuptools import setup, Extension

# extension module
module = Extension('dataman', source=['data_calc.c'])

# running the setup
setup(
    name='dataman',
    version='1.0',
    description='A C extension for mode, median and standard deviation'
    ext_modules=[module]
    )
