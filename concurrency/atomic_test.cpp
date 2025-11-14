#include <gtest/gtest.h>
#include <atomic>
#include <thread>

namespace cao1629 {

TEST(AtomicVarTest, Test1) {
  std::atomic_int count;
  std::condition_variable cv;

  std::atomic<int> count1;
}

}