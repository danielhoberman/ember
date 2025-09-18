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

- This will compile the `_core_operators` module and place it in `dist/`.

---

## 🔹 Install in Editable Mode

```bash
uv pip install -e .
```

- Python will recognize the `ember` package for development.

---

## 🔹 Running Tests

Ember has **Python unit tests** (via `pytest`) and **C++ unit tests** (via GoogleTest, vendored into `extern/googletest`).

### ✅ Python Tests

```bash
uv run pytest
```

### ✅ C++ Tests

First build the project so test executables are available:

```bash
uv build
```

Then run C++ tests with `ctest`:

```bash
uv run ctest --test-dir build --output-on-failure
```

Or run the test binary directly:

```bash
./build/cpp_tests/unit_tests --gtest_list_tests
./build/cpp_tests/unit_tests --gtest_filter=TensorDataTest.*
```

---

## 🔹 Pre-commit Hooks

This repo uses [pre-commit](https://pre-commit.com/) to ensure **linting, type-checking, and tests all pass before committing**.

Install hooks:

```bash
uv run pre-commit install
```

Run all hooks manually:

```bash
uv run pre-commit run --all-files
```

Hooks include:

- **Ruff** (linting & formatting)
- **Mypy** (static type checking)
- **Pytest** (Python unit tests)
- **CTest** (C++ unit tests)

If any check fails, the commit will be blocked.

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

## 🔹 License

MIT License – see `LICENSE` file
