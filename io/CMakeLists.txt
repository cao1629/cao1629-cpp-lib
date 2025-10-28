file(GLOB io_sources "*.cpp")
file(GLOB io_test_sources "*_test.cpp")
list(FILTER io_sources EXCLUDE REGEX ".*_test.cpp")

add_library(io_lib ${io_sources})

target_include_directories(io_lib PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

foreach (io_test ${io_test_sources})
    get_filename_component(test_name ${io_test} NAME_WE)
    add_executable(${test_name} ${io_test})
    target_link_libraries(${test_name} PRIVATE io_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()