#include <gtest/gtest.h>
#include <unordered_set>
#include <classes/point.h>

// Template specialization of std::hash for cao1629::Point
namespace std {
template <>
struct std::hash<cao1629::Point> {
  std::size_t operator()(const cao1629::Point &p) const noexcept {
    // Combine the hash of x and y coordinates
    std::size_t h1 = std::hash<int>{}(p.x());
    std::size_t h2 = std::hash<int>{}(p.y());
    // Simple hash combination using XOR and bit shifting
    return h1 ^ (h2 << 1);
  }
};
}

namespace cao1629 {



TEST(HashTest, Test1) {
}

}