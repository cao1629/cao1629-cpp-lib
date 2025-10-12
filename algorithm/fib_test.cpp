#include <gtest/gtest.h>
#include <algorithm/fib.h>
#include <vector>

namespace cao1629 {

TEST(FibTest, FibRTest) {
  EXPECT_EQ(FibR(1), 1);
  EXPECT_EQ(FibR(2), 2);
  EXPECT_EQ(FibR(3), 3);
  EXPECT_EQ(FibR(4), 5);
  EXPECT_EQ(FibR(5), 8);
  EXPECT_EQ(FibR(6), 13);
  EXPECT_EQ(FibR(7), 21);
  EXPECT_EQ(FibR(8), 34);
  EXPECT_EQ(FibR(9), 55);
  EXPECT_EQ(FibR(10), 89);
}

TEST(FibTest, FibDpTest) {
  EXPECT_EQ(FibDp(1), 1);
  EXPECT_EQ(FibDp(2), 2);
  EXPECT_EQ(FibDp(3), 3);
  EXPECT_EQ(FibDp(4), 5);
  EXPECT_EQ(FibDp(5), 8);
  EXPECT_EQ(FibDp(6), 13);
  EXPECT_EQ(FibDp(7), 21);
  EXPECT_EQ(FibDp(8), 34);
  EXPECT_EQ(FibDp(9), 55);
  EXPECT_EQ(FibDp(10), 89);
}

TEST(FibTest, BasicFibTest) {
  EXPECT_EQ(Fib(1), 1);
  EXPECT_EQ(Fib(2), 2);
  EXPECT_EQ(FibDp(3), 3);
  EXPECT_EQ(FibDp(4), 5);
  EXPECT_EQ(FibDp(5), 8);
  EXPECT_EQ(FibDp(6), 13);
  EXPECT_EQ(FibDp(7), 21);
  EXPECT_EQ(FibDp(8), 34);
  EXPECT_EQ(FibDp(9), 55);
  EXPECT_EQ(FibDp(10), 89);
}


TEST(FibTest, Test1) {
  std::vector<int> v = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  std::vector<int> expected = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
}
}