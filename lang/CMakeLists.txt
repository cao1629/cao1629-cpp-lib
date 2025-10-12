file(GLOB lang_sources "*.cpp")
file(GLOB lang_test_sources "*_test.cpp")
list(FILTER lang_sources EXCLUDE REGEX ".*_test.cpp")

add_library(lang_lib ${lang_sources})

target_include_directories(lang_lib PUBLIC ${CMAKE_SOURCE_DIR})
target_link_libraries(lang_lib INTERFACE classes_lib)

include(GoogleTest)
enable_testing()

foreach (lang_test ${lang_test_sources})
    get_filename_component(test_name ${lang_test} NAME_WE)
    add_executable(${test_name} ${lang_test})
    target_link_libraries(${test_name} PRIVATE lang_lib gtest_main)
    gtest_discover_tests(${test_name})
endforeach()