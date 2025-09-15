from hypothesis import given

from ember import operators

from .strategies import assert_close, small_floats


@given(small_floats, small_floats)
def test_main_ops_matches_python(a: float, b: float) -> None:
    # Test arithmetic operators against Python
    assert_close(operators.mul(a, b), a * b)
    assert_close(operators.add(a, b), a + b)
    assert_close(operators.neg(a), -a)
    assert_close(operators.max(a, b), a if a > b else b)
    if abs(a) > 1e-5:
        assert_close(operators.inv(a), 1.0 / a)


@given(small_floats)
def test_relu(a: float) -> None:
    if a > 0:
        assert_close(operators.relu(a), a)
    if a < 0:
        assert operators.relu(a) == 0.0


@given(small_floats)
def test_id(a: float) -> None:
    assert_close(operators.id(a), a)


@given(small_floats)
def test_lt(a: float) -> None:
    """Check that a - 1.0 is always less than a"""
    assert operators.lt(a - 1.0, a) == 1.0
    assert operators.lt(a, a - 1.0) == 0.0


@given(small_floats)
def test_max(a: float) -> None:
    assert_close(operators.max(a - 1.0, a), a)
    assert_close(operators.max(a, a - 1.0), a)
    assert_close(operators.max(a + 1.0, a), a + 1.0)
    assert_close(operators.max(a, a + 1.0), a + 1.0)


@given(small_floats)
def test_eq(a: float) -> None:
    assert operators.eq(a, a) == 1.0
    assert operators.eq(a, a - 1.0) == 0.0
    assert operators.eq(a, a + 1.0) == 0.0
