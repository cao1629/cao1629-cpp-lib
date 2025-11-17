#include <gtest/gtest.h>
#include <vector>

namespace cao1629 {

int BinarySearch(std::vector<int>& nums, int k) {
  int left = 0;
  int right = nums.size()-1;

  while (left <= right) {
    int mid = (left+right)>>1;
    if (nums[mid] < k) {
      left = mid+1;
    } else if (nums[mid] > k) {
      right = mid-1;
    } else {
      return mid;
    }
  }

  return -1;
}


TEST(BinarySearchTest, Test1) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9};
  int result = BinarySearch(v, 5);
  EXPECT_EQ(result, 4);
}


// Find the first element that is greater than or equal to k
int LowerBound(std::vector<int> &nums, int k) {
  int left = 0;
  int right = nums.size()-1;

  while (left <= right) {
    int mid = (left+right)>>1;

    if (nums[mid] < k) { // nums[:mid] < k, the result must be in nums[mid+1:]
      left = mid+1;
    } else {    // nums[mid:] >= k, but it might not be the first one
      right = mid-1;
    }
  }
  return left;
}


TEST(BinarySearchTest, TestLowerBound) {
  std::vector<int> v{1, 2, 3, 3, 3, 3, 3, 4, 5};
  int result = LowerBound(v, 3);
  EXPECT_EQ(result, 2);

  EXPECT_EQ(LowerBound(v, 0), 0);

  EXPECT_EQ(LowerBound(v, 6), v.size());
}

}