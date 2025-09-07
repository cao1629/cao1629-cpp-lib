#include <gtest/gtest.h>
#include <algorithms/fib.h>

namespace cao1629 {

TEST(FibTest, SimpleTest) {
  EXPECT_EQ(Fib(1), 1);
  EXPECT_EQ(Fib(2), 2);
  EXPECT_EQ(Fib(3), 3);
  EXPECT_EQ(Fib(4), 5);
  EXPECT_EQ(Fib(5), 8);
  EXPECT_EQ(Fib(6), 13);
  EXPECT_EQ(Fib(7), 21);
  EXPECT_EQ(Fib(8), 34);
  EXPECT_EQ(Fib(9), 55);
  EXPECT_EQ(Fib(10), 89);
}

}