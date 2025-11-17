


add_library(skiplist skiplist.cpp)
target_link_libraries(skiplist PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

add_executable(skiplist_test skiplist_test.cpp)
target_link_libraries(skiplist_test PRIVATE skiplist gtest_main)