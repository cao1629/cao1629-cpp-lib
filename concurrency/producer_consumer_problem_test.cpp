#include <gtest/gtest.h>
#include <mutex>
#include <condition_variable>
#include <vector>
#include <thread>

namespace cao1629 {
// unbounded buffer
class ProducerConsumerV1 {
public:
  void Produce(int val) {
    {
      std::unique_lock<std::mutex> lock(mu_);
      q_.push(val);
    }
    cv_.notify_one();
  }

  bool Consume() {
    std::unique_lock<std::mutex> lock(mu_);
    while (q_.empty()) {
      cv_.wait(lock);
    }
    int val = q_.front();
    if (val < 0) {
      return false;
    }

    q_.pop();
    consumed_numbers_.push_back(val);
    return true;
  }

  void Producer() {
    for (int i = 1; i <= 30; i++) {
      Produce(i);
    }

    Produce(-1);
  }

  void Consumer() {
    while (Consume()) {
    }
  }

  void Run() {
    std::thread producer{&ProducerConsumerV1::Producer, this};
    std::vector<std::thread> consumers;
    consumers.reserve(5);
    for (int i = 0; i < 5; i++) {
      consumers.emplace_back(&ProducerConsumerV1::Consumer, this);
    }

    producer.join();
    for (auto& consumer : consumers) {
      consumer.join();
    }
  }

  std::condition_variable cv_;
  std::mutex mu_;
  std::queue<int> q_;
  std::vector<int> consumed_numbers_;
};


TEST(ProducerConsumerTest, TestV1) {
  ProducerConsumerV1 v1;
  v1.Run();
  std::vector<int> expected;
  for (int i = 1; i <= 30; i++) {
    expected.push_back(i);
  }

  EXPECT_EQ(v1.consumed_numbers_, expected);
}


}
