#include <gtest/gtest.h>
#include <vector>

namespace cao1629 {

// 2312 Selling Pieces of Wood
int SellingWood(int m, int n, std::vector<std::vector<int>>& prices) {
  std::vector<std::vector<int>> pr(m+1, std::vector<int>(n+1));
  for (auto& v : prices) {
    pr[v[0]][v[1]] = v[2];
  }

  std::vector<std::vector<int>> dp(m+1, std::vector<int>(n+1));

  for (int i = 1; i <= m; i++) {
    for (int j = 1; j <= n; j++) {
      dp[i][j] = pr[i][j];
      // horizontal
      for (int h = 1; h < i; h++) {
        dp[i][j] = std::max(dp[i][j], dp[h][j]+dp[i-h][j]);
      }

      // vertical
      for (int w = 1; w < j; w++) {
        dp[i][j] = std::max(dp[i][j], dp[i][w]+dp[i][j-w]);
      }
    }
  }

  return dp[m][n];
}


TEST(DpTest, TestSellingWood) {
  std::vector<std::vector<int>> prices{{1, 4, 2}, {2, 2, 7}, {2, 1, 3}};
  int result = SellingWood(3, 5, prices);
  std::cout << result << std::endl;
}

// 1278. Palindrome Partitioning III
int palindromePartition(std::string s, int k) {
  std::vector<std::vector<int>> dp(k+1, std::vector<int>(s.size()+1, s.size()));

  dp[0][0] = 0;

  auto numChanges = [](std::string& s, int l, int r) {
    int result = 0;
    while (l < r) {
      if (s[l] != s[r]) {
        result++;
      }
      l++;
      r--;
    }
    return result;
  };

  for (int p = 1; p <= k; p++) {
    for (int i = 1; i <= s.size(); i++) {
      for (int l = i; l-1 >= p-1; l--) {
        int t = numChanges(s, l-1, i-1);
        dp[p][i] = std::min(dp[p][i], dp[p-1][l-1]+t);
      }
    }
  }

  return dp[k].back();

}

TEST(DpTest, TestPalindromePartition) {
  std::string s = "abc";
  EXPECT_EQ(palindromePartition(s, 2), 1);
}

// 813 Largest Sum of Averages
double largestSumAverages(std::vector<int>& nums, int k) {
  std::vector<double> prefix_sum(nums.size()+1);
  for (int i = 0; i < nums.size(); i++) {
    prefix_sum[i+1] = prefix_sum[i] + nums[i];
  }

  std::vector<std::vector<double>> dp(k+1, std::vector<double>(nums.size()+1, -10000));
  dp[0][0] = 0;

  for (int p = 1; p <= k; p++) {
    for (int i = p; i <= nums.size(); i++) {
      // [l-th : i-th]
      for (int l = p; l <= i; l++) {
        double avg = (prefix_sum[i]-prefix_sum[l-1])/(i-l+1);
        dp[p][i] = std::max(dp[p][i], dp[p-1][l-1]+avg);
      }
    }
  }

  return dp[k].back();
}

TEST(dpTest, Test813) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7};
  EXPECT_EQ(largestSumAverages(v, 4), 20.5);
}


}