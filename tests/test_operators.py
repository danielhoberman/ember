import random
from typing import Callable, Tuple

import math
import pytest
from hypothesis import given

from ember import MathTest
from ember.operators import (
    add,
    eq,
    id,
    inv,
    inv_back,
    log_back,
    lt,
    max,
    mul,
    neg,
    relu,
    relu_back,
    sigmoid,
    sigmoid_back,
)

from .strategies import assert_close, small_floats

# ## Task 0.1 Basic hypothesis tests.


@given(small_floats, small_floats)
def test_same_as_python(x: float, y: float) -> None:
    """Check that the main operators all return the same value of the python version"""
    assert_close(mul(x, y), x * y)
    assert_close(add(x, y), x + y)
    assert_close(neg(x), -x)
    assert_close(max(x, y), x if x > y else y)
    if abs(x) > 1e-5:
        assert_close(inv(x), 1.0 / x)


@given(small_floats)
def test_relu(a: float) -> None:
    if a > 0:
        assert_close(relu(a), a)
    if a < 0:
        assert_close(relu(a), 0.0)


@given(small_floats, small_floats)
def test_relu_back(a: float, b: float) -> None:
    if a > 0:
        assert_close(relu_back(a, b), b)
    if a < 0:
        assert_close(relu_back(a, b), 0.0)


@given(small_floats, small_floats)
def test_sigmoid_back(a: float, b: float) -> None:
    sig = 1 / (1 + math.exp(-a))  # sigmoid
    expected = b * sig * (1 - sig)  # ✅ correct derivative
    actual = sigmoid_back(a, b)
    assert_close(actual, expected)


@given(small_floats)
def test_id(a: float) -> None:
    assert_close(id(a), a)


@given(small_floats)
def test_lt(a: float) -> None:
    """Check that a - 1.0 is always less than a"""
    assert lt(a - 1.0, a) == 1.0
    assert lt(a, a - 1.0) == 0.0


@given(small_floats)
def test_max(a: float) -> None:
    assert_close(max(a - 1.0, a), a)
    assert_close(max(a, a - 1.0), a)
    assert_close(max(a + 1.0, a), a + 1.0)
    assert_close(max(a, a + 1.0), a + 1.0)


@given(small_floats)
def test_eq(a: float) -> None:
    assert eq(a, a) == 1.0
    assert eq(a, a - 1.0) == 0.0
    assert eq(a, a + 1.0) == 0.0


# ## Task 0.2 - Property Testing

# Implement the following property checks
# that ensure that your operators obey basic
# mathematical rules.


@given(small_floats)
def test_sigmoid(a: float) -> None:
    """Check properties of the sigmoid function, specifically
    * It is always between 0.0 and 1.0.
    * one minus sigmoid is the same as sigmoid of the negative
    * It crosses 0 at 0.5
    * It is  strictly increasing.
    """
    assert 0.0 <= sigmoid(a) <= 1.0
    assert_close(1 - sigmoid(a), sigmoid(-a))
    assert sigmoid(0) == 0.5
    assert sigmoid(a) <= sigmoid(a + 1)


@given(small_floats, small_floats, small_floats)
def test_transitive(a: float, b: float, c: float) -> None:
    """Test the transitive property of less-than (a < b and b < c implies a < c)"""
    assert a < c if a < b and b < c else True


def test_symmetric() -> None:
    """Write a test that ensures that :func:`minitorch.operators.mul` is symmetric, i.e.
    gives the same value regardless of the order of its input.
    """
    a = random.uniform(5.0, 10.0)
    b = random.uniform(5.0, 10.0)
    assert mul(a, b) == pytest.approx(mul(b, a))


def test_distribute() -> None:
    r"""Write a test that ensures that your operators distribute, i.e.
    :math:`z \times (x + y) = z \times x + z \times y`
    """
    x = random.uniform(5.0, 10.0)
    y = random.uniform(5.0, 10.0)
    z = random.uniform(5.0, 10.0)
    assert mul(z, add(x, y)) == pytest.approx(mul(z, x) + mul(z, y))


def test_other() -> None:
    # Check commutativity of addition
    a = random.uniform(0, 10)
    b = random.uniform(0, 10)
    assert add(a, b) == pytest.approx(add(b, a))


# ## Generic mathematical tests

# For each unit this generic set of mathematical tests will run.


one_arg, two_arg, _ = MathTest._tests()


@given(small_floats)
@pytest.mark.parametrize("fn", one_arg)
def test_one_args(fn: Tuple[str, Callable[[float], float]], t1: float) -> None:
    name, base_fn = fn
    base_fn(t1)


@given(small_floats, small_floats)
@pytest.mark.parametrize("fn", two_arg)
def test_two_args(
    fn: Tuple[str, Callable[[float, float], float]], t1: float, t2: float
) -> None:
    name, base_fn = fn
    base_fn(t1, t2)


@given(small_floats, small_floats)
def test_backs(a: float, b: float) -> None:
    relu_back(a, b)
    inv_back(a + 2.4, b)
    log_back(abs(a) + 4, b)
