#include <thread>
#include <iostream>
#include <list>


class background_task {
public:
  void operator()() const {
    for (int i = 0; i < 10; i++) {
      std::cout << "background task: " << i << std::endl;
    }
  }
};

struct func {
  int &i;
  func(int &i_) : i(i_) {}
  void operator()() {
    for (int j = 0; j < 1000000; j++) {
      std::cout << "func: " << i << std::endl;
    }
  }
};

void oops() {
  int some_local_state = 0;
  func my_func(some_local_state);
  std::thread my_thread(my_func);
  my_thread.detach();
}


std::list<int> some_list;


int main(int argc, char const *argv[]) {


  return 0;
}
