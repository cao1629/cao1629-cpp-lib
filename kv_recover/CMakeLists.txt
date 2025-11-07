


add_library(kv_store kv_store.cpp)

target_include_directories(kv_store PUBLIC ${CMAKE_SOURCE_DIR})

add_executable(kv_store_test kv_store_test.cpp)

include(GoogleTest)
enable_testing()

target_link_libraries(kv_store_test PRIVATE kv_store gtest_main)

