#include <numeric>
#include <gtest/gtest.h>
#include <vector>

namespace cao1629 {

// 494. Target Sum
int targetSum(std::vector<int> &nums, int target) {
  int sum = std::accumulate(nums.cbegin(), nums.cend(), 0);
  if ((sum+target)%2 != 0 || sum+target < 0) {
    return 0;
  }

  int capacity = (sum+target)/2;
  int n = nums.size();
  std::vector<std::vector<int>> dp(n+1, std::vector<int>(capacity+1, 0));

  dp[0][0] = 1;
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= capacity; j++) {
      if (j >= nums[i-1]) {
        dp[i][j] = dp[i-1][j] + dp[i-1][j-nums[i-1]];
      } else {
        dp[i][j] = dp[i-1][j];
      }
    }
  }

  return dp[n][capacity];
}

TEST(Knapsack01Test, TestTargetSum) {
  std::vector<int> nums{1,1,1,1,1};
  int result = targetSum(nums, 3);
  EXPECT_EQ(result, 5);
}


// Given an array, does it have a subset whose sum equals to 0?
// [-1, 1, 4, 5, 8]


}