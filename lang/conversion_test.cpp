#include <gtest/gtest.h>


namespace cao1629 {

TEST(ConversionTest, TestCharType) {

  // (1) 0xFF is an int. 0x00 00 FF FF
  // (2) convert it into a char  0xFF FF   narrowing conversion
  // (3) char is signed 8 bits. so here c is -1
  char c = 0xFF;
  EXPECT_EQ(c, -1);

}


}