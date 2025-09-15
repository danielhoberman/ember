from ._core import (
    mul,
    id,
    add,
    neg,
    lt,
    eq,
    max,
    is_close,
    sigmoid,
    relu,
    log,
    exp,
    inv,
)


# Arithmetic operators
def mul_op(a: float, b: float) -> float:
    """Multiply two numbers via C++ backend."""
    return mul(a, b)


def id_op(a: float) -> float:
    """Identity function."""
    return id(a)


def add_op(a: float, b: float) -> float:
    """Add two numbers via C++ backend."""
    return add(a, b)


def neg_op(a: float) -> float:
    """Negate a number via C++ backend."""
    return neg(a)


def inv_op(a: float) -> float:
    """Multiplicative inverse (1/a) via C++ backend."""
    return inv(a)


# Comparison operators
def lt_op(a: float, b: float) -> float:
    """Return 1.0 if a < b, else 0.0"""
    return lt(a, b)


def eq_op(a: float, b: float) -> float:
    """Return 1.0 if a == b, else 0.0"""
    return eq(a, b)


def max_op(a: float, b: float) -> float:
    """Return the maximum of a and b."""
    return max(a, b)


def is_close_op(a: float, b: float, tol: float = 1e-2) -> float:
    """Return 1.0 if a and b are within tolerance tol, else 0.0"""
    return is_close(a, b, tol)


# Non-linear activations
def sigmoid_op(a: float) -> float:
    """Sigmoid activation function via C++ backend."""
    return sigmoid(a)


def relu_op(a: float) -> float:
    """ReLU activation function via C++ backend."""
    return relu(a)


# Exponentials / logarithms
def log_op(a: float) -> float:
    """Natural logarithm via C++ backend."""
    return log(a)


def exp_op(a: float) -> float:
    """Exponential function e^a via C++ backend."""
    return exp(a)
