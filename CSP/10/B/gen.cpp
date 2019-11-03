#include <bits/stdc++.h>
using namespace std;

int main() {
  srand(time(NULL));
  int n = 5, m = 5, inf = 1e8;
  cout << n << " " << m << endl;
  for(int i = 1; i <= m; ++i) {
    int x = rand() % n + 1, y = rand() % n + 1, z = rand() % inf + 1;
    printf("%d %d %d\n", x, y, z);
  }
  int s = rand() % n + 1;
  printf("%d\n", s);
  return 0;
}