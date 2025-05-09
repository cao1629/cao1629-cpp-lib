#include "t1.h"
#include <iostream>
#include <fmt/core.h>
#include <fmt/ranges.h>
#include <vector>

int main() {
  std::vector<int> v{1,2,3};
  fmt::print("Vector contents: {}\n", v);
}
