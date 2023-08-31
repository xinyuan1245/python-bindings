from distutils.core import setup
from distutils.extension import Extension
from Cython.Build import cythonize

extensions = {
    Extension("cython_example",["cython_example.pyx"],libraries=["dl"])
}

setup(
    ext_modules= cythonize(extensions)
)