file(GLOB concurrency_sources "*.cpp")
file(GLOB concurrency_test_sources "*_test.cpp")
list(FILTER concurrency_sources EXCLUDE REGEX ".*_test.cpp")

add_library(concurrency_lib ${concurrency_sources})
target_include_directories(concurrency_lib PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

foreach (concurrency_test ${concurrency_test_sources})
    get_filename_component(test_name ${concurrency_test} NAME_WE)
    add_executable(${test_name} ${concurrency_test})
    target_link_libraries(${test_name} PRIVATE concurrency_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()


