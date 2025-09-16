#include <pybind11/pybind11.h>
#include "operators.h"

namespace py = pybind11;

PYBIND11_MODULE(_core_operators, m) {
    m.doc() = "Ember low-level numeric ops";

    // =====================
    // Arithmetic
    // =====================
    m.def("_add", &fwd::add, "Add two floats");
    m.def("_mul", &fwd::mul, "Multiply two floats");
    m.def("_neg", &fwd::neg, "Negation (unary minus)");
    m.def("_inv", &fwd::inv, "Multiplicative inverse (1/a)");
    m.def("_id",  &fwd::id,  "Identity function (returns input unchanged)");
    m.def("_max", &fwd::max, "Maximum of two floats");

    // =====================
    // Comparisons
    // =====================
    m.def("_lt", &fwd::lt, "1.0f if a < b else 0.0f");
    m.def("_eq", &fwd::eq, "1.0f if a == b else 0.0f");
    m.def("_is_close", &fwd::is_close,
          py::arg("a"), py::arg("b"), py::arg("tol") = 2e-1f,
          "Check if two floats are close within a tolerance (returns 1.0 or 0.0)");

    // =====================
    // Non-linear activations
    // =====================
    m.def("_relu", &fwd::relu, "ReLU: max(0, a)");
    m.def("_sigmoid", &fwd::sigmoid, "Sigmoid function (numerically stable)");

    // =====================
    // Exponentials / logs
    // =====================
    m.def("_exp", &fwd::exp, "Exponential e^a");
    m.def("_log", &fwd::log, "Natural logarithm ln(a)");

    // =====================
    // Backward
    // =====================
    m.def("_log_back", &bwd::log, "Gradient of log(a)");
    m.def("_inv_back", &bwd::inv, "Gradient of inv(a)");
    m.def("_relu_back", &bwd::relu, "Gradient of relu(a)");
    m.def("_sigmoid_back", &bwd::sigmoid, "Gradient of sigmoid(a)");
    m.def("_exp_back", &bwd::exp, "Gradient of exp(a)");
}
