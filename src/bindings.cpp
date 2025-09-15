#include <pybind11/pybind11.h>
#include "scalar.h"

namespace py = pybind11;

PYBIND11_MODULE(myproject_cpp, m) {
    py::class_<Scalar>(m, "Scalar")
        .def(py::init<float, bool>(), py::arg("value"), py::arg("requires_grad") = false)
        .def_readwrite("value", &Scalar::value)
        .def_readwrite("grad", &Scalar::grad)
        .def("backward", &Scalar::backward)
        .def("__add__", &Scalar::operator+);
}
