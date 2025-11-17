#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>

namespace cao1629 {

// 189. Rotate Array
// rotate an array in place
void rotateArray(std::vector<int> &nums, int k) {

}

// Given an array, test if there is a subset whose sum equals to 0
// [9, -1, 8, 1, 5]
bool ExistSubsetSumZero(std::vector<int> &nums) {
  std::unordered_set<int> sum_set;
  sum_set.insert(0);
  for (auto e : nums) {
    if (sum_set.find(-e) != sum_set.cend()) {
      return true;
    }
    std::vector<int> new_elements;
    new_elements.reserve(sum_set.size());
    for (auto s : sum_set) {
      new_elements.push_back(s+e);
    }
    sum_set.insert(new_elements.cbegin(), new_elements.cend());
  }
  return false;
}

TEST(ArrayTest, TestExistSubsetSumZero) {
  std::vector<int> nums{9, -1, 8, 2, 5, -1};
  EXPECT_TRUE(ExistSubsetSumZero(nums));
}


}