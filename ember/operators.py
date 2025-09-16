# ember/operators.py
"""
High-level Python wrappers for the C++ core operators.

These functions provide user-friendly interfaces with consistent
naming, docstrings, and typing. All operators are delegated to
the compiled C++ backend.
"""

from typing import Union
from . import _core_operators as _C

Number = Union[int, float]


# =====================
# Arithmetic operators
# =====================
def mul(a: Number, b: Number) -> float:
    """Multiply two numbers via C++ backend."""
    return _C._mul(float(a), float(b))


def add(a: Number, b: Number) -> float:
    """Add two numbers via C++ backend."""
    return _C._add(float(a), float(b))


def neg(a: Number) -> float:
    """Negate a number via C++ backend."""
    return _C._neg(float(a))


def inv(a: Number) -> float:
    """Multiplicative inverse (1/a) via C++ backend."""
    return _C._inv(float(a))


def id(a: Number) -> float:
    """Identity function (returns input unchanged)."""
    return _C._id(float(a))


# =====================
# Comparison operators
# =====================
def lt(a: Number, b: Number) -> float:
    """Return 1.0 if a < b, else 0.0."""
    return _C._lt(float(a), float(b))


def eq(a: Number, b: Number) -> float:
    """Return 1.0 if a == b, else 0.0."""
    return _C._eq(float(a), float(b))


def max(a: Number, b: Number) -> float:
    """Return the maximum of a and b via C++ backend."""
    return _C._max(float(a), float(b))


def is_close(a: Number, b: Number, tol: float = 2e-1) -> float:
    """Return 1.0 if |a - b| < tol, else 0.0."""
    return _C._is_close(float(a), float(b), float(tol))


# =====================
# Non-linear activations
# =====================
def sigmoid(a: Number) -> float:
    """Sigmoid activation function via C++ backend."""
    return _C._sigmoid(float(a))


def relu(a: Number) -> float:
    """ReLU activation function via C++ backend."""
    return _C._relu(float(a))


# =====================
# Exponentials / logarithms
# =====================
def log(a: Number) -> float:
    """Natural logarithm via C++ backend."""
    return _C._log(float(a))


def exp(a: Number) -> float:
    """Exponential function e^a via C++ backend."""
    return _C._exp(float(a))


# =====================
# Backward passes
# =====================
def log_back(a: Number, grad: Number) -> float:
    """Backward pass for log: dL/da given upstream gradient."""
    return _C._log_back(float(a), float(grad))


def inv_back(a: Number, grad: Number) -> float:
    """Backward pass for inverse: dL/da given upstream gradient."""
    return _C._inv_back(float(a), float(grad))


def relu_back(a: Number, grad: Number) -> float:
    """Backward pass for ReLU: dL/da given upstream gradient."""
    return _C._relu_back(float(a), float(grad))


def sigmoid_back(a: Number, grad: Number) -> float:
    """Backward pass for sigmoid: dL/da given upstream gradient."""
    return _C._sigmoid_back(float(a), float(grad))


def exp_back(a: Number, grad: Number) -> float:
    """Backward pass for exp: dL/da given upstream gradient."""
    return _C._exp_back(float(a), float(grad))
