#include <gtest/gtest.h>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <thread>
#include <vector>
#include <chrono>
#include <atomic>

namespace cao1629 {


class BlockingQueue {
public:
  BlockingQueue(size_t capacity): capacity_(capacity) {}

  void Push(int val) {
    std::unique_lock<std::mutex> lock(mu_);
    full_.wait(lock, [this] {
      return q_.size() < capacity_;
    });

    q_.push(val);
    empty_.notify_one();
  }

  int Pop() {
    std::unique_lock<std::mutex> lock(mu_);
    empty_.wait(lock, [this] {
      return q_.size() > 0;
    });
    int result = q_.front();
    q_.pop();
    full_.notify_one();
    return result;
  }

private:
  std::queue<int> q_;
  std::mutex mu_;
  std::condition_variable empty_;
  std::condition_variable full_;
  size_t capacity_;
};

TEST(CondVarTest, TestBlockingQueue) {
  BlockingQueue queue(10);

  // Test 1: Basic push and pop
  queue.Push(1);
  queue.Push(2);
  queue.Push(3);

  EXPECT_EQ(queue.Pop(), 1);
  EXPECT_EQ(queue.Pop(), 2);
  EXPECT_EQ(queue.Pop(), 3);

  // Test 2: Multiple producers and consumers
  const int num_producers = 3;
  const int num_consumers = 3;
  const int items_per_producer = 20;

  std::vector<std::thread> producers;
  std::vector<std::thread> consumers;
  std::vector<int> consumed_values;
  std::mutex consumed_mutex; // protect consumed_values

  // Start consumers
  for (int i = 0; i < num_consumers; ++i) {
    consumers.emplace_back([&queue, &consumed_values, &consumed_mutex, items_per_producer, num_producers]() {
      int expected_total = items_per_producer * num_producers / 3;
      for (int j = 0; j < expected_total; ++j) {
        int val = queue.Pop();
        std::lock_guard<std::mutex> lock(consumed_mutex);
        consumed_values.push_back(val);
      }
    });
  }

  // Start producers
  for (int i = 0; i < num_producers; ++i) {
    producers.emplace_back([&queue, i, items_per_producer]() {
      for (int j = 0; j < items_per_producer; ++j) {
        queue.Push(i * 100 + j);
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
      }
    });
  }

  // Wait for all threads to complete
  for (auto& producer : producers) {
    producer.join();
  }

  for (auto& consumer : consumers) {
    consumer.join();
  }

  // Verify all items were consumed
  EXPECT_EQ(consumed_values.size(), num_producers * items_per_producer);

  // Test 3: Verify queue respects capacity (blocking on full)
  BlockingQueue small_queue(2);
  std::atomic<bool> push_blocked(false);
  std::atomic<bool> push_completed(false);

  small_queue.Push(1);
  small_queue.Push(2);

  // Try to push to a full queue - should block
  std::thread blocking_producer([&small_queue, &push_blocked, &push_completed]() {
    push_blocked = true;
    small_queue.Push(3);  // This should block until space is available
    push_completed = true;
  });

  // Give the producer time to block
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  EXPECT_TRUE(push_blocked);
  EXPECT_FALSE(push_completed);

  // Pop an item to make space
  small_queue.Pop();

  // Now the producer should complete
  blocking_producer.join();
  EXPECT_TRUE(push_completed);
}


}