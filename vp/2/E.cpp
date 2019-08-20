#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
struct data {
  int x, y;
} pr[N][N];
int a[N], c[N][N], f[N][N];

void go(int dep, int zt) {
  if(!dep) return ;
  go(dep - 1, pr[dep][zt].x);
  printf("%d ", pr[dep][zt].y);
}

int main() {
  // freopen("quant.in", "r", stdin);
  // freopen("quant.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  int m, s;
  scanf("%d%d", &m, &s);
  for(int i = 0; i < m; ++i)
    for(int j = 0; j < s; ++j) {
      scanf("%d", &c[i][j]);
    }
  memset(f, 0x3f, sizeof f);
  f[0][0] = 0;
  for(int i = 1; i <= n; ++i) {
    for(int j = 0; j < m; ++j) {
      for(int k = 0; k < s; ++k) {
        int pos = f[i - 1][j] + abs(c[j][k] - a[i]);
        if(f[i][k & (m - 1)] > pos) {
          f[i][k & (m - 1)] = pos;
          pr[i][k & (m - 1)] = (data){j, k};
        }
      }
    }
  }
  int be = 0, ans = 1e9;
  for(int i = 0; i < m; ++i) {
    if(ans > f[n][i]) {
      ans = f[n][i];
      be = i;
    }
  }
  printf("%d\n", ans);
  go(n, be);
  return 0;
}