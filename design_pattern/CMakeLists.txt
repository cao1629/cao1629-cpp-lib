file(GLOB design_pattern_sources "*.cpp")
file(GLOB design_pattern_test_sources "*_test.cpp")
list(FILTER design_pattern_sources EXCLUDE REGEX ".*_test.cpp")

add_library(design_pattern_lib ${design_pattern_sources})

target_include_directories(design_pattern_lib PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

foreach (design_pattern_test ${design_pattern_test_sources})
    get_filename_component(test_name ${stl_test} NAME_WE)
    add_executable(${test_name} ${stl_test})
    target_link_libraries(${test_name} PRIVATE design_pattern_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()

