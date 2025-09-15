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

## 🔹 Build Instructions

1. Clone this repo and enter it:

   ```bash
   git clone https://github.com/yourusername/myproject.git
   cd myproject
   ```

2. Create a build directory and configure with CMake:

   ```bash
   cmake -B build -S . -DPYBIND11_PYTHON_VERSION=3.12
   ```

3. Compile:

   ```bash
   cmake --build build
   ```

4. After building, you should see something like:

   ```
   build/myproject.cpython-312-darwin.so
   ```

---

## 🔹 Running the Python Demo

Point `PYTHONPATH` to the `build/` folder so Python can find the module, then run the demo:

```bash
PYTHONPATH=build python3 python/main.py
```

Example output:

```
Hello from Danny, value=5
```

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
