#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = rand() % 1000 + 1;
  printf("%d\n", n);
  for(int i = 1; i <= n; ++i) {
    int pos = rand() % 65536 + 1;
    printf("%d ", pos);
  }
  puts("");
  for(int i = 2; i <= n; ++i) {
    int pos = rand() % (i - 1) + 1;
    printf("%d %d\n", pos, i);
  }
  return 0;
}