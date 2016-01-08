from distutils.core import setup, Extension
import numpy.distutils.misc_util

setup(name="saclibpy", ext_modules=[Extension("saclibpy", sources=["saclibpy.c"], include_dirs=["/home/eamon/software/SacLibPy/include"], library_dirs=["/home/eamon/software/SacLibPy/lib"], libraries=["sac", "sacio", "m"], extra_link_args=["-Wall", "-O2"])], include_dirs=numpy.distutils.misc_util.get_numpy_include_dirs())
