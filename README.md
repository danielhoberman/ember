# Ember

**Ember** is a lightweight numerical computing library with a C++ backend for high-performance scalar operations. It exposes common arithmetic, comparison, activation, and exponential/logarithmic operations to Python via `pybind11`. Ember now also includes Python modules, automatic differentiation, and optimization utilities for building and training neural networks.

---

## 🔹 Features

### **C++ Core Operators**

- Arithmetic: `add`, `sub`, `mul`, `neg`, `inv`, `id`, `max`
- Comparisons: `lt`, `eq`, `is_close`
- Activations: `sigmoid`, `relu`
- Exponential / logarithmic: `exp`, `log`

### **Python Additions**

- **Modules**: Define custom layers and networks by subclassing `ember.Module`.
- **Scalar**: Lightweight scalar type with gradient tracking for automatic differentiation.
- **Autodiff**: Compute derivatives of arbitrary computation graphs using `.backward()`.
- **SGD Optimizer**: Stochastic Gradient Descent to train models with gradient updates.
- **Linear Layers**: Fully connected layers with learnable weights and biases.

---

## 🔹 Build Instructions

1. **Clone the repository:**

```bash
git clone https://github.com/yourusername/ember.git
cd ember
```

2. **Build the C++ extension using `uv`:**

```bash
uv build
```

- This will create a `_core` module inside `dist/` that Python can import.

---

## 🔹 Install in Editable Mode

```bash
uv pip install -e .
```

- Python will recognize the `ember` package for development.

---

## 🔹 Python Usage Example

```python
import ember

# Scalar operations
a = 3.0
b = 4.0
print(ember.add_op(a, b))       # 7.0
print(ember.mul_op(a, b))       # 12.0
print(ember.sigmoid_op(a))      # 0.95257413
print(ember.log_op(b))          # 1.3862944

# Neural network example
from ember import ScalarTrain

trainer = ScalarTrain(hidden_layers=10)
data = ember.datasets
trainer.train(data, learning_rate=0.5)
```

---

## 🔹 Development

- Use `uv` to manage builds and package installation.
- Use `pre-commit` with `ruff` and `mypy` for linting and type checking:

```bash
uv run pre-commit install
uv run pre-commit run --all-files
```

---

## 🔹 License

MIT License – see `LICENSE` file
