file(GLOB data_structures_sources *.cpp)
list(FILTER data_structures_sources EXCLUDE REGEX ".*_test.cpp")
add_library(data_structures_lib ${data_structures_sources})
target_include_directories(data_structures_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)

file(GLOB data_structures_test *_test.cpp)
foreach(test_src ${data_structures_test})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE data_structures_lib GTest::gtest_main)
    gtest_discover_tests(${test_name})
endforeach()