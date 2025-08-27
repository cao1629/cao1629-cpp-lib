#include <gtest/gtest.h>


namespace cao1629 {

template <typename T>
class ArrayOfAnything {
public:

  auto GetSize() -> size_t {
    return size_;
  }

  auto IncreaseSize(int amount) -> size_t {
    size_ += amount;
    return size_;
  }

  void Insert(T item);

private:
  size_t size_;
  T array_[1];
};

template <typename T>
ArrayOfAnything<T>* MakeArray(size_t capacity) {
  auto mem = new char[capacity];
  return reinterpret_cast<ArrayOfAnything<T>*>(mem);
}

}
