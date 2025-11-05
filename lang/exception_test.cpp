#include <gtest/gtest.h>
#include <iostream>
#include <exception>
#include <unordered_set>

namespace cao1629 {


TEST(ExceptionTest, Test1) {
  int a = -1%4;
  std::set<std::pair<int, int>> s;
  if (s.find({1,2}) != s.cend()) {

  }

}

}