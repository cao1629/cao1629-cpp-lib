
add_library(b_plus_tree b_plus_tree_page.cpp b_plus_tree.cpp)
target_link_options(b_plus_tree PUBLIC ${CMAKE_SOURCE_DIR})

include(GoogleTest)
enable_testing()

add_executable(b_plus_tree_test b_plus_tree_test.cpp)
target_link_libraries(b_plus_tree_test PRIVATE b_plus_tree)



