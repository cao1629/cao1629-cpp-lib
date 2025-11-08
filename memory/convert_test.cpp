#include <gtest/gtest.h>


namespace cao1629 {

TEST(ConversionTest, Test1) {

  int v = 1;
  char buffer[4];

  memcpy(buffer, &v, 4);
  EXPECT_EQ(0, memcmp(buffer, &v, 4));
}

}