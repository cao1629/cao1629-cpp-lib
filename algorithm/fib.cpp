


namespace cao1629 {



int FibR(int n) {
  if (n <= 2) {
    return n;
  }
  return FibR(n-1) + FibR(n-2);
}



}
