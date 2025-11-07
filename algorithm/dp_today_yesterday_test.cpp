#include <iostream>
#include <vector>
#include <gtest/gtest.h>

namespace cao1629 {

// 121. Best time to buy and sell stock
int buyAndSellStock(std::vector<int> &prices) {
  int n = prices.size();
  std::vector<std::vector<int>> dp(n, std::vector<int>(2));
  dp[0][0] = -prices[0];

  for (int i = 1; i < n; i++) {
    dp[i][0] = std::max(dp[i-1][0], -prices[i]);
    dp[i][1] = std::max(dp[i-1][1], dp[i-1][0]+prices[i]);
  }

  return dp[n-1][1];
}


TEST(DpTest, TestBuyAndSellStock) {
  std::vector<int> prices{7, 1, 5, 3, 6, 4};
  int result = buyAndSellStock(prices);
  EXPECT_EQ(result, 5);
}

}