add_test([=[HelloTest.BasicAssertions]=]  /home/caoheng/projects/cao1629-cpp-lib/build/HelloWorldTest [==[--gtest_filter=HelloTest.BasicAssertions]==] --gtest_also_run_disabled_tests)
set_tests_properties([=[HelloTest.BasicAssertions]=]  PROPERTIES WORKING_DIRECTORY /home/caoheng/projects/cao1629-cpp-lib/build SKIP_REGULAR_EXPRESSION [==[\[  SKIPPED \]]==])
set(  HelloWorldTest_TESTS HelloTest.BasicAssertions)
