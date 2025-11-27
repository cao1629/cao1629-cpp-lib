#include <iostream>
#include <vector>
#include <unordered_map>

namespace cao1629 {

struct Node {
  int val;
  int count;

};

class Heap {
public:
  int Push(int val) {
    int size = data_.size();
    Node* node = new Node();
    node->val = val;
    node->count = 1;
    data_.push_back(node);
    Swim(size + 1);
    return data_.size();
  }

  int Pop() {
    int top = data_[0]->val;
    int size = data_.size();
    data_.resize(size - 1);
    Sink(0);
    return top;
  }

  int Top() {
    return data_[0]->val;
  }

  int Swim(int idx) {
    // parent
    int p = idx;
    while (p > 1) {
      int parent = idx >> 1;
      if (data_[parent]->val < data_[idx]->val) {
        std::swap(data_[parent], data_[idx]);
      }
      p = parent;
    }
    return p;
  }

  // count--  -> Sink()
  int Sink(int idx) {
    //
    int n = data_.size();
    int p = idx;
    while (p <= n) {
      int left = idx * 2;
      int right = idx * 2 + 1;
      //
      int child;
      if (data_[left]->val < data_[right]->val) {
        child = right;
      }
      else {
        child = left;
      }

      if (data_[p]->val >= data_[child]->val) {
        return p;
      }
      else {
        std::swap(data_[p], data_[child]);
        p = child;
      }
    }

    return p;
  }

  // idx: 1~
  std::vector<Node*> data_;
};


class MostFrequentNumber {
public:
  // return the most frequent value
  // window is full
  int Slide() {
    int left_idx = map[left_element];
    heap.data_[left_idx]->val--;
    heap.Sink(left_idx);

    int next_number = Next();

    if (map.find(next_number) == map.cend()) {
      map[next_number] = heap.Push(next_number);

    } else {
      int idx = map[next_number];
      heap.data_[idx]->val++;
      map[next_number] = heap.Swim(idx);
    }

    return heap.Top();
  }

  void Init() {
    for (int i = 0; i < 5; i++) {
      heap.Push(i);
    }
  }

  int Next() {
    // assert(.....)
    return numbers[cursor++];
  }

  std::vector<int> numbers{6, 1, 8, 9, 10};
  int cursor = 0;

  // number -> heap idx
  std::unordered_map<int, int> map;

  Heap heap;
  int left_element;
};

int main() {
  MostFrequentNumber o;
  o.Init();
  for (int i = 0; i < 5; i++) {
    int result = o.Slide();
    std::cout << result << std::endl;
  }

}

}
