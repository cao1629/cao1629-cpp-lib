cmake_minimum_required(VERSION 3.10)

project(cao1629-cpp-lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

add_subdirectory(googletest)

add_executable(hello_test hello_test.cpp)
target_link_libraries(hello_test GTest::gtest_main)


include(GoogleTest)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")

add_library(HelloWorld hello.cpp)


include_directories(${CMAKE_SOURCE_DIR})


# find_package(GTest REQUIRED)


# target_link_libraries(HelloWorldTest GTest::gtest_main HelloWorld)

# include(GoogleTest)
# gtest_discover_tests(HelloWorldTest)

add_subdirectory(common)

# add_executable(TimeUtilTest time_util_test.cpp)
# target_link_libraries(TimeUtilTest TimeUtil)

add_executable(a1 a1.cpp)

add_executable(a2 a2.cpp)

add_executable(a3 a3.cpp)

target_link_libraries(a2 fmt::fmt)

add_executable(FutureTest future_test.cpp)

add_executable(worker worker.cpp)

find_package(fmt)

include_directories(
    ${CMAKE_SOURCE_DIR})


