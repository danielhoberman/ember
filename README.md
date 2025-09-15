# Ember

**Ember** is a lightweight numerical computing library with a C++ backend for high-performance scalar operations. It exposes common arithmetic, comparison, activation, and exponential/logarithmic operations to Python via `pybind11`.

---

## 🔹 Features

- Header-only C++ operators for:

  - Arithmetic: `add`, `sub`, `mul`, `neg`, `inv`, `id`, `max`
  - Comparisons: `lt`, `eq`, `is_close`
  - Activations: `sigmoid`, `relu`
  - Exponential/logarithmic: `exp`, `log`

- Python bindings via `pybind11` and `uv` for easy import.
- Type-safe wrappers for seamless Python use.

---

## 🔹 Build Instructions

1. **Clone the repository:**

```bash
git clone https://github.com/yourusername/ember.git
cd ember
```

2. **Build the C++ extension using uv:**

```bash
uv build
```

- This will create a `_core` module inside `dist/` that Python can import.

---

## 🔹 Install in editable mode

```bash
uv pip install -e .
```

- Now Python will recognize the `ember` package for development.

---

## 🔹 Running the Demo

```bash
uv run python ember/main.py
```

Example output:

```
=== Basic arithmetic ===
3.0 + 4.0 = 7.0
3.0 * 4.0 = 12.0
3.0 - 4.0 = -1.0
-3.0 = -3.0
1/3.0 = 0.33333334

=== Comparisons ===
3.0 < 4.0 ? 1.0
3.0 == 4.0 ? 0.0
max(3.0, 4.0) = 4.0
is_close(3.0, 4.0) = 0.0

=== Non-linear activations ===
sigmoid(3.0) = 0.95257413
ReLU(-3.0) = 0.0

=== Exponentials / logs ===
exp(3.0) = 20.085537
log(4.0) = 1.3862944
```

---

## 🔹 Usage Example

```python
import ember

a = 3.0
b = 4.0

print(ember.add_op(a, b))       # 7.0
print(ember.mul_op(a, b))       # 12.0
print(ember.sigmoid_op(a))      # 0.95257413
print(ember.log_op(b))          # 1.3862944
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
