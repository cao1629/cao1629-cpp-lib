#include <gtest/gtest.h>


namespace cao1629 {

TEST(TypeTest, Test1) {
  uint8_t i = 0x80;
  uint8_t j = i<<1;
  std::cout << (int)j << std::endl;
}
}