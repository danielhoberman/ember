cmake_minimum_required(VERSION 3.18)
project(ember LANGUAGES CXX)

# Use C++17
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find pybind11
find_package(pybind11 CONFIG REQUIRED)

# Build the pybind11 extension _core
pybind11_add_module(_core
    src/bindings.cpp   # only this file, operators.h is included header-only
)

# Include the folder containing operators.h
target_include_directories(_core PRIVATE include)

# Install the compiled module into the ember package
install(TARGETS _core DESTINATION ember)
