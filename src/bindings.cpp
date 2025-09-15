#include <pybind11/pybind11.h>
#include "operators.h"

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = "Ember low-level numeric ops";

    m.def("mul", &mul, "Multiply two floats");
    m.def("add", &add, "Add two floats");
    m.def("sub", &sub, "Subtract two floats");
}
