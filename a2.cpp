

#include <atomic>
#include <chrono>
#include <thread>
#include <vector>
#include <iostream>

std::vector<int> data;
std::atomic<bool> data_ready{false};

void reader_thread() {
  while (!data_ready.load()) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  std::cout << "The asnwer=" << data[0] << std::endl;
}

void writer_thread() {
  data.push_back(42);
  data_ready.store(true);
}

int main() {
  std::thread t1(reader_thread), t2(writer_thread);
  t1.join();
  t2.join();
}