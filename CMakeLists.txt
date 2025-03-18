cmake_minimum_required(VERSION 3.10)

project(cao1629-cpp-lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)

# enable_testing()

# find_package(GTest REQUIRED)

add_library(HelloWorld hello.cpp)


# target_link_libraries(HelloWorldTest GTest::gtest_main HelloWorld)

# include(GoogleTest)
# gtest_discover_tests(HelloWorldTest)


add_subdirectory(common)

add_executable(TimeUtilTest time_util_test.cpp)
target_link_libraries(TimeUtilTest TimeUtil)

add_executable(a1 a1.cpp)

add_executable(a2 a2.cpp)

target_link_libraries(a2)

add_executable(point point.cpp)