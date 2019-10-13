#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = 50;
  printf("%d\n", n);
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= 20; ++j) {
      int x = rand() % 26;
      printf("%c", char(x + 'a'));
    }
    puts("");
  }
  return 0;
}