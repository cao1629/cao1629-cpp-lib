#include <gtest/gtest.h>
#include <iostream>


namespace cao1629 {

class Base {
public:
  virtual ~Base() = default;

  virtual void foo() {
    std::cout << "Base" << std::endl;
  }
};


class Derived : public Base {
public:
  void foo() override {
    std::cout << "Derived" << std::endl;
  }
};

TEST(oopTest, Test1) {
  Base* b = new Derived();
  b->foo();

  // dynamic_cast succeeds
  Derived* d = dynamic_cast<Derived*>(b);
  EXPECT_EQ(d, b);


  // dynamic_cast fails
  Base* b1 = new Base();
  Derived* d1 = dynamic_cast<Derived*>(b1);
  EXPECT_EQ(d1, nullptr);

}


}