file(GLOB classes_sources "*.cpp")
file(GLOB classes_test_sources "*_test.cpp")
list(FILTER classes_sources EXCLUDE REGEX ".*_test.cpp")

add_library(classes_lib ${classes_sources})

target_include_directories(classes_lib PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

foreach (classes_test ${classes_test_sources})
    get_filename_component(test_name ${classes_test} NAME_WE)
    add_executable(${test_name} ${classes_test})
    target_link_libraries(${test_name} PRIVATE classes_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()