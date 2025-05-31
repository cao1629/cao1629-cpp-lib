#include <thread>


int main(int argc, char const *argv[]) {
  std::thread t1;
  t1 = std::thread([]() {
    // This thread does nothing but sleep for 1 second
    std::this_thread::sleep_for(std::chrono::seconds(1));
  });
  t1.join();
  return 0;
}
