#include <gtest/gtest.h>
#include <vector>

namespace cao1629 {

// 15. 3Sum
std::vector<std::vector<int>> threeSum(std::vector<int> nums) {
  std::sort(nums.begin(), nums.end());
  std::vector<std::vector<int>> ans;
  int n = nums.size();

  for (int i = 0; i < n-2; i++) {
    if (i > 0 && nums[i] == nums[i-1]) {
      continue;
    }

    if (nums[i] + nums[i+1] + nums[i+2] > 0) {
      break;
    }

    if (nums[i] + nums[n-2] + nums[n-1] < 0) {
      continue;
    }

    int p1 = i+1, p2 = n-1;

    while (p1 < p2) {
      int k = nums[i] + nums[p1] + nums[p2];

      if (k < 0) {
        p1++;
      } else if (k > 0) {
        p2--;
      } else {
        ans.push_back({nums[i], nums[p1], nums[p2]});
        do { p1++; } while (p1 < p2 && nums[p1] == nums[p1-1]);
        do { p2--; } while (p1 < p2 && nums[p2] == nums[p2+1]);
      }
    }
  }

  return ans;
}


TEST(TwoPtrTest, Test3Sum) {
  std::vector<int> v{-1, 0, 1, 2, -1, -4};
  auto ans = threeSum(v);
  std::vector<std::vector<int>> expected{{-1, -1, 2}, {-1, 0, 1}};
  EXPECT_EQ(ans, expected);
}


int trapRainWater(std::vector<int> &height) {
  int result = 0;
  int n = height.size();
  int left = 0;
  int right = n-1;
  int left_max = height[left];
  int right_max = height[right];
  while (left < right) {
    // Why it works?
    // height[left] < height[right], then we know height[left] < max_right
    // the amount of water slot left can trap is determined by the minimum of left_max
    // and right_max.
    if (height[left] < height[right]) {
      result += left_max - height[left];
      left++;
      left_max = std::max(left_max, height[left]);
    } else {
      result += right_max - height[right];
      right--;
      right_max = std::max(right_max, height[right]);
    }
  }
  return result;
}

TEST(TwoPtrTest, TestTrapRainWater) {
  std::vector<int> v1{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  auto ans1 = trapRainWater(v1);
  EXPECT_EQ(ans1, 6);

  std::vector<int> v2{4, 2, 0, 3, 2, 5};
  auto ans2 = trapRainWater(v2);
  EXPECT_EQ(ans2, 9);
}

}