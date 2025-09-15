# MyProject — Minimal C++ ↔ Python Extension with pybind11

This is a **minimal example** of building a C++ library and exposing it to Python using **pybind11** + **CMake**.
It shows how to:

- Write a C++ class (`MyClass`)
- Bind it to Python with `pybind11`
- Build it into a shared library (`.so` / `.pyd`)
- Import it directly from Python

---

## 🔹 Project Structure

```
myproject/
├── CMakeLists.txt          # Build configuration
├── include/
│   └── myclass.h           # C++ class declaration
├── src/
│   ├── myclass.cpp         # C++ class implementation
│   └── bindings.cpp        # pybind11 bindings
├── python/
│   └── demo.py             # Example Python usage
└── build/                  # (created after compilation)
```

---

## 🔹 Prerequisites

Make sure you have:

- Python ≥ 3.9
- CMake ≥ 3.15
- A C++17 compiler (clang++ / g++)
- pybind11 (header-only library)

You can install `pybind11` in your Python environment:

```bash
brew install pybind11
```

---

## 🔹 Build & Install with uv

1. Clone this repo and enter it:

   ```bash
   git clone https://github.com/yourusername/myproject.git
   cd myproject
   ```

2. Sync dependencies (this sets up a virtual environment with `scikit-build-core` + `pybind11`):

   ```bash
   uv sync
   ```

3. Build and install the C++ extension in editable mode:

   ```bash
   uv pip install -e .
   ```

   This will automatically configure and compile the project using CMake under the hood, then install the built Python extension into your environment.

---

## 🔹 Running the Python Demo

Run the demo script inside the `uv` environment:

```bash
uv run python python/main.py
```

Example output:

```
Hello from Danny, value=5
```

---

👉 With this setup, you no longer need to manually set `PYTHONPATH` or touch the `build/` folder. Everything is handled by `uv` + `scikit-build-core`.

---

Do you also want me to add an **optional dev loop** section to the README (using `watchfiles` or `entr`) so users can auto-rebuild whenever they edit C++ files?

---

## 🔹 Notes

- The module name is set in `bindings.cpp`:

  ```cpp
  PYBIND11_MODULE(myproject, m) {
      // ...
  }
  ```

  This defines the Python import name (`import myproject`).

- On Windows, the output file will be a `.pyd` instead of `.so`.
