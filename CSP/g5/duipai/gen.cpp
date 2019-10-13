#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 8;
  printf("%d\n", n);
  for(int i = 2; i <= n; ++i) {
    int x = rand() % (i - 1) + 1;
    printf("%d %d\n", i, x);
  }
  int q = rand() % 5 + 1;
  printf("%d\n", q);
  for(int o = 1; o <= q; ++o) {
    while(1) {
    int x = rand() % n + 1, y = rand() % n + 1, z = rand() % n + 1;
    if(x == y || y == z || x == z) continue;
    printf("%d %d %d\n", x, y, z);
    break;
    }
  }
  return 0;
}