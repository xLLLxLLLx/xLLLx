#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n, mk[1 << N];
char lx[1 << N][N];

void check(int x, int y) {
  int res = 0;
  for(int i = 1; i <= n; ++i) {
    if(lx[x][i] != lx[y][i]) ++res;
  }
  if(res < n / 2) {
    printf("%d %d\n", x, y);
    puts("!!!");
  }
}

int main() {
  scanf("%d", &n);
  int tot = (1 << n);
  for(int i = 1; i <= tot; ++i) {
    scanf("%s", lx[i] + 1);
    int pos = 0;
    for(int j = 1; j <= n; ++j) {
      pos = pos * 2 + lx[i][j] - '0';
    }
    mk[pos] = 1;
  }
  for(int i = 1; i <= tot; ++i) {
    if(i == tot) check(i, 1);
    else check(i, i + 1);
  }
  return 0;
}