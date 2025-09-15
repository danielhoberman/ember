cmake_minimum_required(VERSION 3.18)
project(myproject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(pybind11 REQUIRED)

pybind11_add_module(myproject_cpp src/bindings.cpp src/myclass.cpp)

target_include_directories(myproject_cpp PRIVATE include)