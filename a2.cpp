#include <future>
#include <iostream>
#include <thread>
#include <chrono>

void calculate_square(std::promise<int> *p, int x) {
  int result = x * x;
  std::this_thread::sleep_for(std::chrono::seconds(2));
  p->set_value(result);
}

int main(int argc, char const *argv[]) {
  // std::promise is a producer who can only produce once
  std::promise<int> p;

  // std::future is a consumer who can only consume once
  std::future<int> f = p.get_future();

  // Launch a thread to calculate the square of 9
  std::thread task(calculate_square, &p, 9);

  int result = f.get();
  std::cout << "The square of 9 is " << result << std::endl;

  task.join();

  return 0;
}