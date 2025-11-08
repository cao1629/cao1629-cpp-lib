cmake_minimum_required(VERSION 3.10)

project(cao1629-cpp-lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(algorithm)
add_subdirectory(lang)
add_subdirectory(memory)
add_subdirectory(stl)
add_subdirectory(googletest)
add_subdirectory(classes)
add_subdirectory(concurrency)
add_subdirectory(io)
add_subdirectory(kv_recover)
add_subdirectory(external_sort)
