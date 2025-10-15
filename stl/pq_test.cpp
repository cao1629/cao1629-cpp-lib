#include <gtest/gtest.h>
#include <queue>
#include <iostream>

namespace cao1629 {

TEST(PriorityQueueTest, TestBasic) {
  std::priority_queue<int, std::vector<int>, std::less<int>> q;

  std::vector<int> v{1, 10, 2, 9, 3, 8, 4, 7, 6};

  for (int i = 0; i < 5; i++) {
    q.push(v[i]);
  }


  for (int i = 5; i < v.size(); i++) {
    q.pop();
    q.push(v[i]);
  }

  while (!q.empty()) {
    std::cout << q.top() << std::endl;
    q.pop();
  }
}

}