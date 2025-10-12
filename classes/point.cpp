#include "point.h"

namespace cao1629 {

std::string Point::ToString() const {
  return "(" + std::to_string(x_) + ", " + std::to_string(y_) + ")";
}
}