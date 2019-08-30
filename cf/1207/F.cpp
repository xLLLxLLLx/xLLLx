#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10, M = 700;
int a[N], b[M + 10][M + 10];

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int tp, x, y;
    scanf("%d%d%d", &tp, &x, &y);
    if(tp == 1) {
      a[x] += y;
      for(int i = 1; i <= M; ++i)
        b[i][x % i] += y;
    } else {
      if(x <= M) printf("%d\n", b[x][y]);
      else {
        int sum = 0;
        for(int i = y; i <= 500000; i += x)
          sum += a[i];
        printf("%d\n", sum);
      }
    }
  }
  return 0;
}