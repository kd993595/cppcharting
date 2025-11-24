cmake_minimum_required(VERSION 3.20)
project(graphlib LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library sources
add_library(graphlib
    src/core/graph.cpp
    src/2d/bar.cpp
)

find_package(raylib REQUIRED)

# Header include directory
target_include_directories(graphlib
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Link raylib to the library
target_link_libraries(graphlib PUBLIC raylib)

# Example executable (optional)
add_executable(demo examples/main.cpp)
target_link_libraries(demo PRIVATE graphlib raylib)
