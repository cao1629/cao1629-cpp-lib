#include <algorithm/fib.h>


namespace cao1629 {


int FibR(int n) {
  if (n <= 2) {
    return n;
  }
  return FibR(n-1) + FibR(n-2);
}

int FibDp(int n) {
  if (n <= 2) {
    return n;
  }

  int dp[n+1];
  dp[0] = 0;
  dp[1] = 1;
  dp[2] = 2;
  for (int i = 3; i <= n; i++) {
    dp[i] = dp[i-2] + dp[i-1];
  }
  return dp[n];
}

int Fib(int n) {
  if (n <= 2) {
    return n;
  }

  int x = 1;
  int y = 2;

  for (int i = 2; i < n; i++) {
    int t = x;
    x = y;
    y += t;
  }

  return y;
}

}
