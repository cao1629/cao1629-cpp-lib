#include <gtest/gtest.h>
#include <vector>
#include <unordered_map>

namespace cao1629 {

class Heap {

public:

  bool IsEmpty() {
    return v.size() <= 1;
  }

  void Push(int val) {
    v.push_back(val);
    Swim(v.size()-1);
  }

  int Pop() {
    int top = v[1];
    v[1] = v.back();
    v.resize(v.size()-1);
    Sink(1);
    return top;
  }

  void Swim(int idx) {
    int p = idx;
    while (p > 1) {
      int parent = p>>1;
      if (v[parent] < v[p]) {
        std::swap(v[parent], v[p]);
        p = parent;
      } else {
        return;
      }
    }
  }

  void Sink(int idx) {
    int p = idx;

    while (2*p <= v.size()-1) {

      int child;
      if (2*p+1 <= v.size()-1) {
        if (v[2*p] < v[2*p+1]) {
          child = 2*p+1;
        } else {
          child = 2*p;
        }
      } else {
        child = 2*p;
      }

      if (v[child] > v[p]) {
        std::swap(v[child], v[p]);
        p = child;
      } else {
        return;
      }
    }
  }

  std::vector<int> v{-1};
};


TEST(HeapTest, TestHeap) {
  // std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
  // Heap heap;
  // for (auto e : v) {
  //   heap.Push(e);
  // }
  //
  // std::vector<int> result;
  // while (!heap.IsEmpty()) {
  //   result.push_back(heap.Pop());
  // }

  //
  // std::unordered_map<int, std::unordered_map<int, int>> m;
  // std::string s = "abcd";
  // std::reverse(s.begin(), s.end());

  const int v = 1;

}

}