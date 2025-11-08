#include <gtest/gtest.h>
#include "classes/point.h"

namespace cao1629 {

TEST(SharedPtrTest, TestBasic) {
  {
    std::shared_ptr<Point> p = std::make_shared<Point>(1, 2);

    // increase a new reference
    std::shared_ptr<Point> p2 = p;
  }

  {
    std::shared_ptr<Point> p = std::make_shared<Point>(1, 2);

    // move the ownership
    // destructor will be called
    std::shared_ptr<Point> p3 = std::move(p);
  }

  {
    std::shared_ptr<Point> p = std::make_shared<Point>(1, 2);

    // reference count decreaes
    p.reset();

    bool empty = false;
    if (!p) {
      empty = true;
    }
    EXPECT_EQ(empty, true);

    // another way
    // p = nullptr;
  }

}

}