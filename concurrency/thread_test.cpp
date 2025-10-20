#include <gtest/gtest.h>
#include <thread>
#include <iostream>

namespace cao1629 {

TEST(ThreadTest, TestCreateThread) {
  auto task = []() {
    for (int i = 0; i < 10; i++) {
      std::cout << i << std::endl;
    }
  };

  std::thread t1{task};
  std::thread t2{task};

  t1.join();
  t2.join();
}

}