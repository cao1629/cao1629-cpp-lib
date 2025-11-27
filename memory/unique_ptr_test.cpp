#include <gtest/gtest.h>
#include <classes/point.h>

#include <utility>

namespace cao1629 {

TEST(UniquePtrTest, Test1) {
  auto p = std::make_unique<Point>(1, 2);
  // p is reset to nullptr, Point's destructor is invoked
  p.reset();


  auto p2 = std::make_unique<Point>(3, 4);

  // equal to
  // p.reset(p2.release())
  p = std::move(p2);


}


TEST(UniqueTest, Test2) {
  std::cout << sizeof(std::shared_ptr<Point>) << std::endl;
}

}