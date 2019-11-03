#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = rand() % 5 + 1, m = rand() % 5 + 1;
  printf("%d %d\n", n, m);
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      int x = rand() % 26;
      printf("%c", (char)(x + 'a'));
    }
    puts("");
  }
  int inf = 1e6;
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= m; ++j) {
      int x = rand() % inf + 1;
      printf("%d ", x);
    }
    puts("");
  }
  return 0;
}