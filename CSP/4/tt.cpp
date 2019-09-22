#include <bits/stdc++.h>
using namespace std;

int main() {
  int n = 1e5, m = 3e5;
  printf("%d %d 0\n", n, m);
  for(int i = 1; i <= m; ++i) {
    int x = rand() % n + 1, y = rand() % n + 1;
    int z = rand() % 1000000 + 1;
    printf("%d %d %d\n", x, y, z);
  }
  return 0;
}