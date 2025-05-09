#include <iostream>
#include <thread>

struct foo {
  void operator()() {
    std::cout << "Hello, world!" << std::endl;
  }

  foo() {
    std::cout << "foo constructor" << std::endl;
  }

  foo(foo &&o) {
    std::cout << "foo move constructor" << std::endl;
  }

  foo(const foo &o) {
    std::cout << "foo copy constructor" << std::endl;
  }

  ~foo() {
    std::cout << "foo destructor" << std::endl;
  }


};


int main(int argc, char const *argv[]) {
  
  return 0;
}