#include <gtest/gtest.h>
#include <list>

#include <unordered_set>
namespace cao1629 {

TEST(listTest, TestRemove) {
  std::list<int> l{1, 2, 3, 4, 5, 5, 6, 7, 8, 9, 10};
  l.remove(5);
  std::list<int> expected{1, 2, 3, 4, 6, 7, 8, 9, 10};
  EXPECT_EQ(l, expected);

  l.remove_if([](auto& e) {
    return e%2 == 0;
  });

  std::list<int> expected1{1, 3, 7, 9};
  EXPECT_EQ(l, expected1);



}

TEST(listTest, Test4) {
  std::list<int> l;
  std::vector<int> v;
}


}