#include <mutex>
#include <optional>
#include <iostream>

int main(int argc, char* argv[]) {
  std::string x{"XXX"};
  std::optional<std::string> y = std::move(x);
  std::cout << x << std::endl;
}
