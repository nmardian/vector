cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(Vector)

add_library(VectorLib)

add_subdirectory(src)
add_subdirectory(test)