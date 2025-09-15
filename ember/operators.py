from ._core import mul, add, sub


def mul_op(a: float, b: float) -> float:
    """Multiply two numbers via C++ backend."""
    return mul(a, b)


def add_op(a: float, b: float) -> float:
    return add(a, b)


def sub_op(a: float, b: float) -> float:
    return sub(a, b)
