#include <gtest/gtest.h>
#include <vector>
#include <list>

namespace cao1629 {


TEST(StlAlgorithmsTest, LowerBoundTest) {
  std::vector<int> v{1, 3, 5, 7, 9, 11};
  auto it = std::lower_bound(v.begin(), v.end(), 6);
  EXPECT_EQ(*it, 7);

  auto it2 = std::lower_bound(v.begin(), v.end(), 15);
  auto d = std::distance(v.begin(), it2);
  EXPECT_EQ(d, 6);

  // With a binary predicate
  std::vector<std::string> sv{"A", "BB", "CCC", "DDDD", "EEEEE"};
  auto sit = std::lower_bound(sv.begin(), sv.end(), 3,
    [](const std::string &a, int b) { return a.size() < b; });
  EXPECT_EQ(*sit, "CCC");
}


TEST(StlAlgorithmsTest, SortTest) {
  std::vector<int> v{1, 9, 2, 8, 3, 7, 4, 6};
  std::sort(v.begin(), v.end());
  EXPECT_EQ(v, (std::vector<int>{1, 2, 3, 4, 6, 7, 8, 9}) );
}

TEST(StlAlgorithmsTest, IteratorTest) {
  std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  EXPECT_EQ(*(v.begin()+2), 3);

  std::list<int> l;
  for (int i = 1; i <= 10; i++) {
    l.push_back(i);
  }
  // EXPECT_EQ(*(l.begin()+2), 3);
}


}



