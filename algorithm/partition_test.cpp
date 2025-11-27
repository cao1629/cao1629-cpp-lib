#include <gtest/gtest.h>
#include <vector>

namespace cao1629 {

// [1,2,3] ->
// [1], [2], [3]
// [1,2], [3]
// [1], [2,3]
// [1,2,3]
class Partition {
public:
  std::vector<int> nums;
  std::vector<std::vector<int>> cur;
  std::vector<std::vector<std::vector<int>>> result;

  Partition(std::vector<int> &nums): nums(nums) {}

  // whether we cut after the n-index element
  void dfs(int n) {
    if (n >= nums.size()) {
      result.push_back(cur);
      return;
    }

    for (int i = n; i < nums.size(); i++) {
      std::vector<int> v;
      for (int k = n; k <= i; k++) {
        v.push_back(nums[k]);
      }
      cur.push_back(v);
      dfs(i+1);
      cur.pop_back();
    }
  }

  std::vector<std::vector<std::vector<int>>> solve() {
    dfs(0);
    return result;
  }
};


TEST(ParitionTest, TestPartition) {
  std::vector<int> nums{1, 2};
  Partition solver(nums);
  auto result = solver.solve();
  std::sort(result.begin(), result.end());
  std::vector<std::vector<std::vector<int>>> expected{{{1},{2}}, {{1,2}}};
  EXPECT_EQ(result, expected);
}

// [1, 2, 3] -> [1][2][3]  [1,2][3]  [1][2,3]   [1][2][3]
class Partition2 {
public:

  void run(std::vector<int>& nums) {
    dfs(nums, 0);
  }

  // idx: next number I will choose
  void dfs(std::vector<int>& nums, int idx) {
    if (idx == nums.size()) {
      result.push_back(cur);
      return;
    }
    // idx~n
    for (int i = idx; i <= nums.size()-1; i++) {
      std::vector<int> v;
      for (int k = idx; k <= i; k++) {
        v.push_back(nums[k]);
      }
      cur.push_back(v);
      dfs(nums, i+1);
      cur.pop_back();
    }
  }

  std::vector<std::vector<int>> cur;
  std::vector<std::vector<std::vector<int>>> result;
};

TEST(partition_test, test1) {
  std::vector<int> v{1,2,3};
  Partition2 o;
  o.run(v);
  int a = 1;

  std::unordered_map<int, int> m;
}

}