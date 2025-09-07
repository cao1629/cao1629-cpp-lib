file(GLOB algorithm_sources "*.cpp")
file(GLOB algorithm_test_sources "*_test.cpp")
list(FILTER algorithm_sources EXCLUDE ${algorithm_test_sources})
file(GLOB algorithm_headers "*.h")

add_library(algorithms_lib ${algorithm_sources})

target_include_directories(algorithms_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)

foreach (algorithm_test ${algorithm_test_sources})
    get_filename_component(test_name ${algorithm_test} NAME_WE)
    add_executable(${test_name} ${algorithm_test})
    target_link_libraries(${test_name} PRIVATE algorithms_lib bustub gtest_main)
    gtest_discover_tests(${test_name})
endforeach()
