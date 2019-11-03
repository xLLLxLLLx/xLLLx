#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int basen = 1000, basew = 10000;
  int n = basen;
  printf("%d\n", n);
  for(int i = 0; i <= n; ++i) {
    int x = rand() % basew + 1, y = rand() % basew + 1;
    printf("%d %d\n", x, y);
  }
  return 0;
}