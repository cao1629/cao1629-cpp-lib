#include <gtest/gtest.h>



namespace cao1629 {

TEST(cstringTest, TestMemcpy) {
  char b1[5] = {1, 2, 3, 4, 5};
  char b2[5] = {1, 2, 8, 4, 3};
  char b3[5] = {1, 2, 3, 5, 4};

  // return value of memcmp: difference between the first different bytes
  EXPECT_EQ(-5, memcmp(b1, b2, 5));
  EXPECT_EQ(1, memcmp(b3, b1, 5));
}

}