cmake_minimum_required(VERSION 3.18)
project(ember LANGUAGES CXX)

# === Global C++ settings ===
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# === pybind11 extension ===
find_package(pybind11 CONFIG REQUIRED)

pybind11_add_module(_core_operators
    src/operators_bindings.cpp   # only this file, operators.h is included header-only
)
target_include_directories(_core_operators PRIVATE include)

install(TARGETS _core_operators DESTINATION ember)

# === Ember C++ library (non-Python parts) ===
add_library(ember
    src/tensor/tensor_data.cpp
)
target_include_directories(ember PUBLIC include)

# === GoogleTest + Unit Tests ===
enable_testing()
add_subdirectory(extern/googletest)  # vendored gtest
add_subdirectory(cpp_tests)          # your test folder
