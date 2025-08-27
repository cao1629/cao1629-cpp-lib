#include <algorithm>
#include <cassert>
#include <complex>
#include <iostream>
#include <list>
#include <cstring>
#include <stack>

struct Data {
  void *element;
};

int main() {
  std::list<int> l;
  for (int i = 0; i < 5; i++) {
    l.push_back(i);
  }

}