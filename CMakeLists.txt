cmake_minimum_required(VERSION 3.20)
project(chartastic LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Use C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Library sources
add_library(chartastic
    src/2d/bar.cpp
    src/2d/area.cpp
    src/2d/scatter.cpp
    src/2d/line.cpp
    src/2d/hist.cpp
    src/2d/box.cpp
    src/2d/pie.cpp
    src/2d/facetgrid.cpp
    src/3d/bar.cpp
    src/3d/pie.cpp
)

find_package(raylib REQUIRED)

# Header include directory
target_include_directories(chartastic
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

# Link raylib to the library
target_link_libraries(chartastic PUBLIC raylib)

# Example executables
add_executable(bar_example examples/bar_example.cpp)
target_link_libraries(bar_example PRIVATE chartastic raylib)

add_executable(area_example examples/area_example.cpp)
target_link_libraries(area_example PRIVATE chartastic raylib)

add_executable(scatter_example examples/scatter_example.cpp)
target_link_libraries(scatter_example PRIVATE chartastic raylib)

add_executable(line_example examples/line_example.cpp)
target_link_libraries(line_example PRIVATE chartastic raylib)

add_executable(hist_example examples/hist_example.cpp)
target_link_libraries(hist_example PRIVATE chartastic raylib)

add_executable(box_example examples/box_example.cpp)
target_link_libraries(box_example PRIVATE chartastic raylib)

add_executable(pie_example examples/pie_example.cpp)
target_link_libraries(pie_example PRIVATE chartastic raylib)

add_executable(facetgrid_example examples/facetgrid_example.cpp)
target_link_libraries(facetgrid_example PRIVATE chartastic raylib)

add_executable(bar3d_example examples/bar3d_example.cpp)
target_link_libraries(bar3d_example PRIVATE chartastic raylib)

add_executable(pie3d_example examples/pie3d_example.cpp)
target_link_libraries(pie3d_example PRIVATE chartastic raylib)
