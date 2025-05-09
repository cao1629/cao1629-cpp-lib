#include <thread>
#include <iostream>
#include <condition_variable>

class Worker {
private:
  bool running_;
  int count_;
public: 

  Worker(): running_(false) {
    std::cout << "Worker created" << std::endl;
    count_ = 0;
  }

  void Start() {
    // mutex_.lock();
    running_ = true;
    // mutex_.unlock();
    std::cout << "Worker started" << std::endl;
    
    while (running_) {
      // Simulate work
      std::cout << "Worker is working: " << count_++ << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "Worker finished work" << std::endl;
  }

  void Stop() {
    // std::unique_lock<std::mutex> lock(mutex_);
    running_ = false;
    std::cout << "Worker stopped" << std::endl;
  }

};


int main(int argc, char const *argv[]) {
  Worker *worker = new Worker();
  std::thread background_thread(&Worker::Start, worker);
  std::cout << "aaa" << std::endl;
  std::this_thread::sleep_for(std::chrono::seconds(3));
  worker->Stop();
  background_thread.join();
}
