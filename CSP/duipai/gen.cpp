#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = 1000;
  printf("%d\n", n);
  for(int o = 2; o <= n; ++o) {
    int x = rand() % (o - 1) + 1;
    printf("%d %d\n", x, o);
  }
  return 0;
}