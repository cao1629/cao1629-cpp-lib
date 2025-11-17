#include <gtest/gtest.h>


namespace cao1629 {

TEST(AlgorithmTest, TestSortByCompositeKey) {
  std::vector<std::vector<int>> v{
    {1,10}, {2, 9}, {2, 8}, {3, 6}
  };

  auto cmp = [](const std::vector<int> &a, const std::vector<int> &b) -> bool {
    if (a[0] == b[0]) {
      return a[1] > b[1];
    }

    return a[0] < b[0];
  };

  // comparator needed by std::sort: if a < b, return true. Otherwise, a >= b, return false.
  std::sort(v.begin(), v.end(), cmp);

  for (const auto &w : v) {
    std::cout << "{" << w[0] << ", " << w[1] << "}, ";
  }
}

// the first item that is greater than or equal to k
TEST(AlgorithmTest, TestLowerBound) {
  std::vector<int> v{1, 2, 3, 4, 5, 5, 6, 7, 8};
  auto it = std::lower_bound(v.begin(), v.end(), 5);
  auto idx = std::distance(v.begin(), it);
  EXPECT_EQ(idx, 4);
}

}