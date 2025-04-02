#include <future>
#include <iostream>

void producer(std::promise<int> *p) {
  // for (int i = 0; i < 10; i++) {
    p->set_value(10);
    std::cout << "Produced: " << 10<< std::endl;
  // }
}

void consumer(std::future<int> *f) {
  // for (int i = 0; i < 10; i++) {
    int value = f->get();
    std::cout << "Consumed: " << value << std::endl;
  // }
}

int main(int argc, char const *argv[]) {
  std::promise<int> p;
  std::future<int> f = p.get_future();

  std::thread t1(consumer, &f);
  std::thread t2(producer, &p);

  t1.join();
  t2.join();
  return 0;
}
