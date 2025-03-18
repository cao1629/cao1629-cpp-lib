#include "time_util.h"
#include <ctime>

auto TimeUtil::GetCurrTime() -> std::string {
  std::time_t now = std::time(nullptr);
  
  return std::ctime(&now);
}

