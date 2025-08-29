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

  void Insert(T &item) {

  }

  void Remove(int index) {

  }

  auto Find(T &key) -> size_t {

  }


  auto GetItem(int index) -> T& {
    return array_[index];
  }

private:
  size_t size_;
  T array_[1];
};

template <typename T>
auto StringOf(T &item) -> std::string {
  return item.ToString();
}

// Capacity is a very large number.
template <typename T>
ArrayOfAnything<T>* MakeArray(size_t capacity) {
  auto mem = new char[capacity];
  return reinterpret_cast<ArrayOfAnything<T>*>(mem);
}


TEST(ArrayOfAnythingTest, SimpleTest) {

}

}
