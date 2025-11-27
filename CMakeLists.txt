cmake_minimum_required(VERSION 3.10)

project(cao1629-cpp-lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(subdirs
        googletest algorithm lang memory stl classes concurrency io
        kv_recover extendable_hash external_sort b_plus_tree interview
)

foreach (subdir ${subdirs})
    add_subdirectory(${subdir})
endforeach ()