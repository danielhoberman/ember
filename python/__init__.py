# python/myproject_cpp/__init__.py

from . import myproject_cpp  # import the compiled pybind11 module

# Expose classes/functions at the top level
Scalar = myproject_cpp.Scalar
