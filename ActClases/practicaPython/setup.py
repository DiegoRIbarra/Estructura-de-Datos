from setuptools import setup
from Cython.Build import cythonize

# Script para compilar el código Cython
setup(
    name='MergeSort Cython',
    ext_modules=cythonize("mergeSort_cython.pyx"),
    zip_safe=False,
)
