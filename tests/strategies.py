from hypothesis import settings
from hypothesis.strategies import floats, integers

from ember.operators import is_close

settings.register_profile("ci", deadline=None)
settings.load_profile("ci")


small_ints = integers(min_value=1, max_value=3)
small_floats = floats(min_value=-100, max_value=100, allow_nan=False)
med_ints = integers(min_value=1, max_value=20)


def assert_close(a: float, b: float, tol: float = 1e-2) -> None:
    assert is_close(a, b, tol), f"Failure: x={a} y={b}"
