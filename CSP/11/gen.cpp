#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = 50, m = 50, mod = 1e9 + 7, base = 1e9 + 6;
  printf("%d %d\n", n, m);
  for(int i = 1; i <= m; ++i) {
    int x = rand() % n;
    printf("%d ", x);
  }
  puts("");
  for(int i = 1; i <= m; ++i) {
    int x = rand() % base + 1;
    printf("%d ", x);
  }
  puts("");
  for(int i = 1; i <= m; ++i) {
    int x = rand() % mod;
    printf("%d ", x);
  }
  puts("");
  for(int i = 1; i <= m; ++i) {
    int x = rand() % mod;
    printf("%d ", x);
  }
  puts("");
  return 0;
}