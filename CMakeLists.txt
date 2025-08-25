# Minimum version of CMake required
cmake_minimum_required(VERSION 3.31.0)

# Optional: Set C++ standard (e.g., C++20)
set(CMAKE_23_COMPILER /opt/homebrew/opt/llvm/bin/clang)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# The name of your project
project(GoFPractice CXX)

add_executable(GofExec main.cpp)

add_subdirectory(FactoryPattern)

target_include_directories(GofExec PRIVATE FactoryPattern/)

