#include <gtest/gtest.h>
#include "hello.h"

TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE("hello", "world");
  // Expect two strings to be equal.
  EXPECT_STREQ("hello", "hello");
  // Expect two integers to be equal.
  EXPECT_EQ(7 * 6, 42);
  // Expect two integers not to be equal.
  EXPECT_NE(7 * 6, 43);
  // Expect a condition to be true.
  EXPECT_TRUE(7 * 6 == 42);
  // Expect a condition to be false.
  EXPECT_FALSE(7 * 6 == 43);

}

