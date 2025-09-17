cmake_minimum_required(VERSION 3.18)
project(ember LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pybind11
find_package(pybind11 CONFIG REQUIRED)

# Build the pybind11 extension _core_operators
pybind11_add_module(_core_operators
    src/operators_bindings.cpp   # only this file, operators.h is included header-only
)

# Include the folder containing operators.h
target_include_directories(_core_operators PRIVATE include)

# Install the compiled module into the ember package
install(TARGETS _core_operators DESTINATION ember)

# Testing
enable_testing()
add_subdirectory(cpp_tests)
