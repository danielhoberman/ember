from myproject_cpp import Scalar

a = Scalar(3.0, requires_grad=True)
b = Scalar(5.0, requires_grad=True)
c = a + b
print(c.value)  # 8.0
c.backward()
print(a.grad)   # 1.0
print(b.grad)   # 1.0