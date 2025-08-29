file(GLOB stl_test_sources *.cpp)


include(GoogleTest)

foreach(stl_test_src ${stl_test_sources})
    get_filename_component(test_name ${stl_test_src} NAME_WE)
    add_executable(${test_name} ${stl_test_src})
    target_link_libraries(${test_name} PRIVATE memory_lib GTest::gtest_main o_lib)
    gtest_discover_tests(${test_name})
endforeach()


