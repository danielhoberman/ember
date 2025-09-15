#include <pybind11/pybind11.h>
#include "myclass.h"

namespace py = pybind11;

PYBIND11_MODULE(myproject, m) {
    py::class_<MyClass>(m, "MyClass")
        .def(py::init<std::string, int>())
        .def("greet", &MyClass::greet)
        .def("set_value", &MyClass::set_value)
        .def("get_value", &MyClass::get_value);
}