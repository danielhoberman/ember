import ember

# Create some scalar objects
a = ember.Scalar(3.0)
b = ember.Scalar(5.0)

# Perform some operations
c = a + b
d = c * a
e = d.log()

print("Forward results:")
print("a =", a.data)
print("b =", b.data)
print("c = a + b =", c.data)
print("d = c * a =", d.data)
print("e = exp(d) =", e.data)

# Run backward to compute gradients
e.backward()

print("\nGradients:")
print("da =", a.derivative)
print("db =", b.derivative)
print("dc =", c.derivative)
print("dd =", d.derivative)
