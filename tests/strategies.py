from ember import operators
from hypothesis import settings
from hypothesis.strategies import floats, integers

# =====================
# Hypothesis settings
# =====================
settings.register_profile("ci", deadline=None)
settings.load_profile("ci")

# =====================
# Strategies
# =====================
# Integers
small_ints = integers(min_value=1, max_value=3)
med_ints = integers(min_value=1, max_value=20)

# Floats
# Avoid subnormal numbers (<1e-7) to prevent ReLU/backprop underflow issues
small_floats = floats(
    min_value=-100.0, max_value=100.0, allow_nan=False, allow_infinity=False, width=32
).filter(lambda x: abs(x) >= 1e-7)


# =====================
# Assertion helper
# =====================
def assert_close(a: float, b: float) -> None:
    assert operators.is_close(a, b), "Failure x=%f y=%f" % (a, b)
