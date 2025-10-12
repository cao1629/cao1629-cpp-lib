file(GLOB memory_sources "*.cpp")
file(GLOB memory_test_sources "*_test.cpp")
list(FILTER memory_sources EXCLUDE REGEX ".*_test.cpp")

add_library(memory_lib ${memory_sources})

target_include_directories(memory_lib PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(memory_lib INTERFACE classes_lib)

include(GoogleTest)
enable_testing()

foreach (memory_test ${memory_test_sources})
    get_filename_component(test_name ${memory_test} NAME_WE)
    add_executable(${test_name} ${memory_test})
    target_link_libraries(${test_name} PRIVATE memory_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()