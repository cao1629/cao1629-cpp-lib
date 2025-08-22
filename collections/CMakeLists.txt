file(GLOB collections_sources *.cpp)
list(FILTER collections_sources EXCLUDE REGEX ".*_test.cpp")
add_library(collections_lib ${collections_sources})
target_include_directories(collections_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

include(GoogleTest)

file(GLOB collections_test *_test.cpp)
foreach(test_src ${collections_test})
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  target_link_libraries(${test_name} PRIVATE collections_lib GTest::gtest_main)
  gtest_discover_tests(${test_name})
endforeach()
