

add_library(external_sort external_sort.cpp)

target_include_directories(external_sort PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(external_sort_test external_sort_test.cpp)

target_link_libraries(external_sort_test PRIVATE external_sort gtest_main)
