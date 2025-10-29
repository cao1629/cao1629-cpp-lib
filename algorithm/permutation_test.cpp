#include <gtest/gtest.h>
#include <vector>
#include <unordered_set>

namespace cao1629 {

// 46. Permutations
// no duplicates
class PermutationI {
public:
  std::vector<std::vector<int>> result;
  std::unordered_set<int> visited;
  std::vector<int> cur;

  // n: how many elements we visited so far
  // start from 0
  void dfs(std::vector<int> &nums, int n) {
    if (n == nums.size()) {
      result.push_back(cur);
      return;
    }

    for (int i = 0; i < nums.size(); i++) {
      if (visited.find(nums[i]) == visited.cend()) {
        visited.insert(nums[i]);
        cur.push_back(nums[i]);
        dfs(nums, n+1);
        visited.erase(nums[i]);
        cur.pop_back();
      }
    }
  }

  void run(std::vector<int> &nums) {
    result.clear();
    visited.clear();
    cur.clear();
    dfs(nums, 0);
    std::sort(result.begin(), result.end());
  }
};

// another solution
class PermutationI2 {
public:
  std::vector<std::vector<int>> result;

  void run(std::vector<int> &nums) {
    result.clear();
    dfs(nums, 0);
    std::sort(result.begin(), result.end());
  }

  // n indicates the index we're working on
  // start from 0
  void dfs(std::vector<int> &nums, int n) {
    if (n == nums.size()) {
      // copy
      result.push_back(nums);
      return;
    }

    for (int i = n; i < nums.size(); i++) {
      std::swap(nums[i], nums[n]);
      dfs(nums, n+1);
      std::swap(nums[i], nums[n]);
    }
  }
};



TEST(PermutationTest, TestPermutationI) {
  std::vector<int> nums{1,2,3};
  std::vector<std::vector<int>> expected{{1,2,3},{1,3,2},{2,1,3},{2,3,1},{3,1,2},{3,2,1}};
  PermutationI solution;
  solution.run(nums);
  EXPECT_EQ(solution.result, expected);

  PermutationI2 solution2;
  solution2.run(nums);
  EXPECT_EQ(solution2.result, expected);
}


// 47. Permutation II
// with duplicates
// [1,1,2] -> [1,1,2], [1,2,1], [2,1,1]
class PermutationII {
public:
  std::vector<std::vector<int>> result;
  // now we insert index rather than value
  std::unordered_set<int> visited;
  std::vector<int> cur;

  void run(std::vector<int> &nums) {
    result.clear();
    visited.clear();
    cur.clear();
    dfs(nums, 0);
    std::sort(result.begin(), result.end());
  }

  void dfs(std::vector<int> &nums, int n) {
    if (n == nums.size()) {
      result.push_back(cur);
      return;
    }

    std::unordered_set<int> s;
    for (int i = 0; i < nums.size(); i++) {
      if (visited.find(i) == visited.cend()) {
        if (s.find(nums[i]) == s.cend()) {
          s.insert(nums[i]);
          visited.insert(i);
          cur.push_back(nums[i]);
          dfs(nums, n+1);
          cur.pop_back();
          visited.erase(i);
        }
      }
    }
  }
};


TEST(PermutationTest, TestPermutationII) {
  std::vector<int> nums{1,1,2};
  std::vector<std::vector<int>> expected{{1,1,2}, {1,2,1},{2,1,1}};
  PermutationII solution;
  solution.run(nums);
  EXPECT_EQ(solution.result, expected);
}

}