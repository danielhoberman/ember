#include <pybind11/pybind11.h>
#include "operators.h"

namespace py = pybind11;

PYBIND11_MODULE(_core, m) {
    m.doc() = "Ember low-level numeric ops";

    // =====================
    // Arithmetic
    // =====================
    m.def("add", &add, "Add two floats");
    m.def("mul", &mul, "Multiply two floats");
    m.def("neg", &neg, "Negation (unary minus)");
    m.def("inv", &inv, "Multiplicative inverse (1/a)");
    m.def("id", &id, "Identity function (returns input unchanged)");
    m.def("max", &max, "Maximum of two floats");

    // =====================
    // Comparisons
    // =====================
    m.def("lt", &lt, "1.0f if a < b else 0.0f");
    m.def("eq", &eq, "1.0f if a == b else 0.0f");
    m.def("is_close", &is_close, py::arg("a"), py::arg("b"), py::arg("tol") = 1e-2f,
          "Check if two floats are close within a tolerance");

    // =====================
    // Non-linear activations
    // =====================
    m.def("relu", &relu, "ReLU: max(0, a)");
    m.def("sigmoid", &sigmoid, "Sigmoid function");

    // =====================
    // Exponentials / logs
    // =====================
    m.def("exp", &expf_op, "Exponential e^a");
    m.def("log", &logf_op, "Natural logarithm ln(a)");
}
