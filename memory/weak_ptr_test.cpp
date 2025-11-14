#include <gtest/gtest.h>
#include <memory>


namespace cao1629 {

struct Node {
  int val_;
  std::shared_ptr<Node> prev_;


  // when a weak_ptr points to an object, the reference count of the object doesn't increase
  // when reference count drops to 0, the object is destroyed even if some weak_ptr still points to it.
  // lock() returns a shared_ptr or nullptr
  // expire() checks if the object is destroyed
  // use_count() returns the reference count
  std::weak_ptr<Node> next_;
};

TEST(WeakPtrTest, Test1) {
  auto a = std::make_shared<Node>();
  auto b = std::make_shared<Node>();

  a->next_ = b;
  b->prev_ = a;
}

}