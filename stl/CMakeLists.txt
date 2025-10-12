file(GLOB stl_sources "*.cpp")
file(GLOB stl_test_sources "*_test.cpp")
list(FILTER stl_sources EXCLUDE REGEX ".*_test.cpp")

add_library(stl_lib ${stl_sources})

target_include_directories(stl_lib PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

foreach (stl_test ${stl_test_sources})
    get_filename_component(test_name ${stl_test} NAME_WE)
    add_executable(${test_name} ${stl_test})
    target_link_libraries(${test_name} PRIVATE stl_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()