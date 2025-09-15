from ._core_operators import (
    _mul,
    _id,
    _add,
    _neg,
    _lt,
    _eq,
    _max,
    _is_close,
    _sigmoid,
    _relu,
    _log,
    _exp,
    _inv,
    _log_back,
    _exp_back,
    _relu_back,
    _sigmoid_back,
    _inv_back,
)


# Arithmetic operators
def mul(a: float, b: float) -> float:
    """Multiply two numbers via C++ backend."""
    return _mul(a, b)


def id(a: float) -> float:
    """Identity function."""
    return _id(a)


def add(a: float, b: float) -> float:
    """Add two numbers via C++ backend."""
    return _add(a, b)


def neg(a: float) -> float:
    """Negate a number via C++ backend."""
    return _neg(a)


def inv(a: float) -> float:
    """Multiplicative inverse (1/a) via C++ backend."""
    return _inv(a)


# Comparison operators
def lt(a: float, b: float) -> float:
    """Return 1.0 if a < b, else 0.0"""
    return _lt(a, b)


def eq(a: float, b: float) -> float:
    """Return 1.0 if a == b, else 0.0"""
    return _eq(a, b)


def max(a: float, b: float) -> float:
    """Return the maximum of a and b."""
    return _max(a, b)


def is_close(a: float, b: float, tol: float = 1e-2) -> float:
    """Return 1.0 if a and b are within tolerance tol, else 0.0"""
    return _is_close(a, b, tol)


# Non-linear activations
def sigmoid(a: float) -> float:
    """Sigmoid activation function via C++ backend."""
    return _sigmoid(a)


def relu(a: float) -> float:
    """ReLU activation function via C++ backend."""
    return _relu(a)


# Exponentials / logarithms
def log(a: float) -> float:
    """Natural logarithm via C++ backend."""
    return _log(a)


def exp(a: float) -> float:
    """Compute e^a using the C++ backend."""
    return _exp(a)


def log_back(a: float, grad: float) -> float:
    """Backward pass for log: dL/da given upstream gradient."""
    return _log_back(a, grad)


def inv_back(a: float, grad: float) -> float:
    """Backward pass for inverse: dL/da given upstream gradient."""
    return _inv_back(a, grad)


def relu_back(a: float, grad: float) -> float:
    """Backward pass for ReLU: dL/da given upstream gradient."""
    return _relu_back(a, grad)


def sigmoid_back(a: float, grad: float) -> float:
    """Backward pass for sigmoid: dL/da given upstream gradient."""
    return _sigmoid_back(a, grad)


def exp_back(a: float, grad: float) -> float:
    """Backward pass for exp: dL/da given upstream gradient."""
    return _exp_back(a, grad)
