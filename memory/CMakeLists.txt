file(GLOB memory_sources *.cpp)
list(FILTER memory_sources EXCLUDE REGEX ".*_test.cpp")
add_library(memory_lib ${memory_sources})
target_include_directories(memory_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)

file(GLOB memory_test *_test.cpp)
foreach(test_src ${memory_test})
    get_filename_component(test_name ${test_src} NAME_WE)
    add_executable(${test_name} ${test_src})
    target_link_libraries(${test_name} PRIVATE memory_lib GTest::gtest_main)
    gtest_discover_tests(${test_name})
endforeach()

include_directories(${PROJECT_SOURCE_DIR})