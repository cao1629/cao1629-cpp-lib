#include <gtest/gtest.h>
#include <vector>

namespace cao1629 {

// 78. Subset
// no duplicates
class Subset {
public:
  std::vector<std::vector<int>> result;
  std::vector<int> nums;
  std::vector<int> cur;

  Subset(std::vector<int> &nums): nums(nums) {}

  // we're going to look at whether nums[n] is going to be picked
  void dfs(int n) {
    if (n >= nums.size()) {
      result.push_back(cur);
      return;
    }
    // not pick
    dfs(n+1);

    // pick
    cur.push_back(nums[n]);
    dfs(n+1);
    cur.pop_back();
  }

  std::vector<std::vector<int>> solve() {
    dfs(0);
    return result;
  }
};

class Subset2 {
public:
  std::vector<std::vector<int>> result;
  std::vector<int> nums;
  std::vector<int> cur;

  Subset2(std::vector<int> &nums): nums(nums) {}

  void dfs(int n) {
    result.push_back(cur);

    for (int i = n; i < nums.size(); i++) {
      cur.push_back(nums[i]);
      dfs(i+1);
      cur.pop_back();
    }
  }

  std::vector<std::vector<int>> solve() {
    dfs(0);
    return result;
  }
};

TEST(CombinationTest, TestSubset) {
  std::vector<int> nums{1,2};
  Subset solver1(nums);
  auto result1 = solver1.solve();
  std::sort(result1.begin(), result1.end());

  Subset2 solver2(nums);
  auto result2 = solver2.solve();
  std::sort(result2.begin(), result2.end());


  std::vector<std::vector<int>> expected{{}, {1}, {1, 2}, {2}};
  EXPECT_EQ(result1, expected);
  EXPECT_EQ(result2, expected);
}
}