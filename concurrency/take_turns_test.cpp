#include <gtest/gtest.h>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>
#include <chrono>

namespace cao1629 {


TEST(TakeTurnsTest, Test1) {

  int num_threads = 10;
  std::mutex mu;
  std::condition_variable cv;
  std::vector<std::thread> threads;
  threads.reserve(num_threads);
  int cur = 0;

  for (int i = 0; i < num_threads; i++) {
    threads.emplace_back([i, &cur, &mu, &cv]() {
      for (;;) {
        std::unique_lock<std::mutex> lock(mu);
        while (cur != i) {
          cv.wait(lock);
        }
        std::cout << i << std::endl;
        cur++;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        cv.notify_all();
      }
    });
  }

  for (int i = 0; i < num_threads; i++) {
    threads[0].join();
  }
}

}