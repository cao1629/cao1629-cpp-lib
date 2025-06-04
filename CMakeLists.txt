cmake_minimum_required(VERSION 3.10)

project(cao1629-cpp-lib VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

enable_testing()

# include(FetchContent)
# FetchContent_Declare(
#   googletest
#   URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
# )
# FetchContent_MakeAvailable(googletest)

add_subdirectory(googletest)

add_library(HelloWorld hello.cpp)

add_executable(HelloWorldTest hello_test.cpp)
target_link_libraries(HelloWorldTest HelloWorld)

include_directories(${CMAKE_SOURCE_DIR})

include(GoogleTest)
gtest_discover_tests(HelloWorldTest)

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

target_link_libraries(a2)

add_executable(point point.cpp)

add_executable(FutureTest future_test.cpp)

add_executable(employee employee.cpp)

add_executable(worker worker.cpp)

find_package(fmt)

include_directories(
    ${CMAKE_SOURCE_DIR})

target_link_libraries(a2 fmt::fmt)