#include <gtest/gtest.h>
#include <atomic>
#include <thread>

namespace cao1629 {

TEST(ConcurrencyTest, Test1) {
  std::atomic_int count;
  std::condition_variable cv;

  std::atomic<int> count1;
}


TEST(ConcurrencyTest, TestRaceConditionCounter) {
  unsigned long counter = 0;

  std::thread t1([&counter]() {
    for (unsigned long i = 0; i < 1000000; i++) {
      counter++;
    }
  });


  std::thread t2([&counter]() {
  for (unsigned long i = 0; i < 1000000; i++) {
    counter++;
  }
});

  t1.join();
  t2.join();

  std::cout << counter << std::endl;
}






}