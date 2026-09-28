"""
Setup para compilar el módulo BFS de Cython
"""

from setuptools import setup, Extension
from Cython.Build import cythonize
import numpy as np

extensions = [
    Extension(
        "bfs_cython",
        ["bfs_cython.pyx"],
        include_dirs=[np.get_include()],
    )
]

setup(
    name="BFS Cython",
    ext_modules=cythonize(extensions, language_level=3),
)
