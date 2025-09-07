file(GLOB algorithm_sources "*.cpp")
file(GLOB algorithm_test_sources "*_test.cpp")
list(FILTER algorithm_sources EXCLUDE REGEX ".*_test.cpp")

add_library(algorithm_lib ${algorithm_sources})

target_include_directories(algorithm_lib PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

foreach (algorithm_test ${algorithm_test_sources})
    get_filename_component(test_name ${algorithm_test} NAME_WE)
    add_executable(${test_name} ${algorithm_test})
    target_link_libraries(${test_name} PRIVATE algorithm_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()


