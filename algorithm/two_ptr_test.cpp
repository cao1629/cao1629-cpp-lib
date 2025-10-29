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
  int n = height.size();
  std::vector<int> left_max(n);
  std::vector<int> right_max(n);

  int cur_left_max = 0;
  for (int i = 0; i < n; i++) {
    cur_left_max = std::max(cur_left_max, height[i]);
    left_max[i] = cur_left_max;
  }

  int cur_right_max = 0;
  for (int i = n-1; i >= 0; i--) {
    cur_right_max = std::max(cur_right_max, height[i]);
    right_max[i] = cur_right_max;
  }


  int result = 0;
  for (int i = 1; i < n-1; i++) {
    result += std::min(left_max[i], right_max[i]) - height[i];
  }

  return result;
}

int trapRainWater2(std::vector<int> &height) {
  int result = 0;
  int n = height.size();
  int left = 0;
  int right = n-1;
  int left_max = 0;
  int right_max = 0;
  while (left <= right) {
    left_max = std::max(left_max, height[left]);
    right_max = std::max(right_max, height[right]);
    if (left_max < right_max) {
      result += left_max - height[left];
      left++;
    } else {
      result += right_max - height[right];
      right--;
    }
  }
  return result;
}

TEST(TwoPtrTest, TestTrapRainWater) {
  std::vector<int> v1{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1};
  auto ans1 = trapRainWater(v1);
  auto ans2 = trapRainWater2(v1);
  EXPECT_EQ(ans1, 6);
  EXPECT_EQ(ans2, 6);
}

}