cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(mandelbrot-gen)

include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(mandelbrot-gen src/Main.cpp src/ArgUtils.cpp)

find_package(PNG REQUIRED)
include_directories(${PNG_INCLUDE_DIR})
target_link_libraries(mandelbrot-gen ${PNG_LIBRARY})
