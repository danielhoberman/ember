# main.py
import ember

# Test values
a = 3.0
b = 4.0

print("=== Basic arithmetic ===")
print(f"{a} + {b} = {ember.add_op(a, b)}")
print(f"{a} * {b} = {ember.mul_op(a, b)}")
print(f"-{a} = {ember.neg_op(a)}")
print(f"1/{a} = {ember.inv_op(a)}")

print("\n=== Comparisons ===")
print(f"{a} < {b} ? {ember.lt_op(a, b)}")
print(f"{a} == {b} ? {ember.eq_op(a, b)}")
print(f"max({a}, {b}) = {ember.max_op(a, b)}")
print(f"is_close({a}, {b}) = {ember.is_close_op(a, b)}")

print("\n=== Non-linear activations ===")
print(f"sigmoid({a}) = {ember.sigmoid_op(a)}")
print(f"ReLU({-a}) = {ember.relu_op(-a)}")

print("\n=== Exponentials / logs ===")
print(f"exp({a}) = {ember.exp_op(a)}")
print(f"log({b}) = {ember.log_op(b)}")
