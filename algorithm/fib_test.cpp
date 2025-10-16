#include <gtest/gtest.h>
#include <vector>

namespace cao1629 {

int fib(int n) {
  if (n <= 2) {
    return n;
  }

  int x = 1;
  int y = 2;
  for (int i = 3; i <= n; i++) {
    int t = x;
    x = y;
    y += t;
  }

  return y;
}

int fibDp(int n) {
  if (n <= 2) {
    return n;
  }

  int dp[n+1];
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 2;

  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i-1] + dp[i-2];
  }

  return dp[n];
}


int fibRecursive(int n) {
  if (n <= 2) {
    return n;
  }

  return fibRecursive(n - 1) + fibRecursive(n - 2);
}

TEST(FibTest, TestFib) {
  EXPECT_EQ(fib(2), 2);
  EXPECT_EQ(fib(3), 3);
  EXPECT_EQ(fib(4), 5);
  EXPECT_EQ(fib(5), 8);
  EXPECT_EQ(fib(6), 13);
  EXPECT_EQ(fib(7), 21);
  EXPECT_EQ(fib(8), 34);
}


TEST(FibTest, TestFibDp) {
  EXPECT_EQ(fibDp(2), 2);
  EXPECT_EQ(fibDp(3), 3);
  EXPECT_EQ(fibDp(4), 5);
  EXPECT_EQ(fibDp(5), 8);
  EXPECT_EQ(fibDp(6), 13);
  EXPECT_EQ(fibDp(7), 21);
  EXPECT_EQ(fibDp(8), 34);
}


TEST(FibTest, TestFibRecursive) {
  EXPECT_EQ(fibRecursive(2), 2);
  EXPECT_EQ(fibRecursive(3), 3);
  EXPECT_EQ(fibRecursive(4), 5);
  EXPECT_EQ(fibRecursive(5), 8);
  EXPECT_EQ(fibRecursive(6), 13);
  EXPECT_EQ(fibRecursive(7), 21);
  EXPECT_EQ(fibRecursive(8), 34);
}



}