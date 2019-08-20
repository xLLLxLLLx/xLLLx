#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = 100;
  printf("%d\n", n);
  for(int i = 1; i <= 100; ++i) {
    int x = i, y = rand() % 5 + 1;
    printf("\"A\" %d %d\n", x, y);
  }
  return 0;
}