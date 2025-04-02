#include <mutex>
#include <queue>
#include <condition_variable>
#include <iostream>
#include <thread>


// Producer-consumer problem
// The queue is unbounded.

static std::queue<int> q;
static std::mutex lock;
static std::condition_variable cv;

void producer() {
  for (int i = 0; i < 10; i++) {
    std::unique_lock<std::mutex> ulock(lock);
    std::cout << "Produced: " << i << std::endl;
    q.push(i);
    cv.notify_one();
  }
}

void consumer() {
  for (int i = 0; i < 10; i++) {

    // RAII: ulock will be released when it goes out of scope.
    std::unique_lock<std::mutex> ulock(lock);

    // Wait until the queue is not empty.
    cv.wait(ulock, []{ return !q.empty(); });
    int value = q.front();
    q.pop();
    std::cout << "Consumed: " << value << std::endl;
  }
}

int main(int argc, char const *argv[]) {
  std::thread t1(consumer);
  std::thread t2(producer);
  t1.join();
  t2.join();
  return 0;
}
