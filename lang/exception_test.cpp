#include <gtest/gtest.h>
#include <iostream>
#include <exception>
#include <unordered_set>

namespace cao1629 {


TEST(ExceptionTest, Test1) {
  // 1111 1111 1111 1111
  // 1111
  char c = 0xFF;
  if (c == 0xFF) {
    std::cout << 1 << std::endl;
  }
  std::cout << static_cast<int>(c) << std::endl;
}

}