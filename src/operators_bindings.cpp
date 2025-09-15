#include <pybind11/pybind11.h>
#include "operators.h"

namespace py = pybind11;

PYBIND11_MODULE(_core_operators, m) {
    m.doc() = "Ember low-level numeric ops";

    // =====================
    // Arithmetic
    // =====================
    m.def("_add", &_add, "Add two floats");
    m.def("_mul", &_mul, "Multiply two floats");
    m.def("_neg", &_neg, "Negation (unary minus)");
    m.def("_inv", &_inv, "Multiplicative inverse (1/a)");
    m.def("_id", &_id, "Identity function (returns input unchanged)");
    m.def("_max", &_max, "Maximum of two floats");

    // =====================
    // Comparisons
    // =====================
    m.def("_lt", &_lt, "1.0f if a < b else 0.0f");
    m.def("_eq", &_eq, "1.0f if a == b else 0.0f");
    m.def("_is_close", &_is_close, py::arg("a"), py::arg("b"), py::arg("tol") = 1e-2f,
          "Check if two floats are close within a tolerance");

    // =====================
    // Non-linear activations
    // =====================
    m.def("_relu", &_relu, "ReLU: max(0, a)");
    m.def("_sigmoid", &_sigmoid, "Sigmoid function");

    // =====================
    // Exponentials / logs
    // =====================
    m.def("_exp", &_exp, "Exponential e^a");
    m.def("_log", &_log, "Natural logarithm ln(a)");

    // =====================
    // Backward
    // =====================
    m.def("_log_back", &_log_back, "Compute gradient of log(a)");
    m.def("_inv_back", &_inv_back, "Comput egradient of inv(a)");
    m.def("_relu_back", &_relu_back, "Compute gradient of relu(a)");
    m.def("_sigmoid_back", &_sigmoid_back, "Comput egradient of sigmoid(a)");
    m.def("_exp_back", &_exp_back, "Compute gradient of exp(a)");

}
