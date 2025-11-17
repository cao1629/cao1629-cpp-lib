

add_library(extendable_hash extendable_hash.cpp)

target_include_directories(extendable_hash PUBLIC ${CMAKE_SOURCE_DIR})


include(GoogleTest)
enable_testing()

add_executable(extendable_hash_test extendable_hash_test.cpp)

target_link_libraries(extendable_hash_test PRIVATE extendable_hash gtest_main)

