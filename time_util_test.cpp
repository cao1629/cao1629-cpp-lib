#include "common/time_util.h"
#include <iostream>

int main(int argc, char const *argv[]){
  std::cout << TimeUtil::GetCurrTime() << std::endl;
  return 0;
}
