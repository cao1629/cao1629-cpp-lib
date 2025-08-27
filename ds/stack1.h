#pragma once

#include <vector>

namespace cao1629 {
template<typename T>
class Stack {
public:
  void Push(const T &elem) {
    elems_.push_back(elem);
  }

  void Pop() {
    if (!IsEmpty()) {
      elems_.pop_back();
    }
  }

  const T &Top() const {
    if (IsEmpty()) {
      throw std::runtime_error("Stack is empty");
    }
    return elems_.back();
  }

  bool IsEmpty() const {
    return elems_.empty();
  }

private:
  std::vector<T> elems_;
};
}

