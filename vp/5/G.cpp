#include <bits/stdc++.h>
using namespace std;
const int N = 201, inf = 1e9;
int yu, tot;
int to[N], g[N][N], vx[N], vy[N], lx[N], ly[N], mx[N], my[N];

bool dfs(int u) {
  vx[u] = 1;
  for(int i = 1; i <= tot; ++i) {
    if(!vy[i]) {
      int pos = lx[u] + ly[i] - g[u][i];
      if(!pos) {
        vy[i] = 1;
        if(!mx[i] || dfs(mx[i])) {
          mx[i] = u;
          my[u] = i;
          return true;
        }
      } else {
        yu = min(yu, pos);
      }
    }
  }
  return false;
}

int main() {
  freopen("keeper.in", "r", stdin);
  freopen("keeper.out", "w", stdout);
  int m, n;
  scanf("%d%d", &m, &n);
  for(int i = 1, num; i <= m; ++i) {
    scanf("%d", &num);
    for(int j = 1, x; j <= num; ++j) {
      scanf("%d", &x);
      g[i][x] = 1000;
    }
  }
  for(int i = 1, x; i <= m; ++i) {
    scanf("%d", &x);
    to[i] = x;
    if(x) g[i][x] = 1001;
  }
  for(int i = 1; i <= m; ++i)
    for(int j = 1; j <= n; ++j)
      lx[i] = max(lx[i], g[i][j]);
  tot = max(n, m);
  for(int i = 1; i <= tot; ++i) {
    for(;;) {
      yu = inf;
      memset(vx, 0, sizeof vx);
      memset(vy, 0, sizeof vy);
      if(dfs(i)) break;
      for(int j = 1; j <= tot; ++j) {
        if(vx[j]) lx[j] -= yu;
        if(vy[j]) lx[j] += yu;
      }
    }
  }
  int ans = 0, be = 0;
  for(int i = 1; i <= m; ++i) {
    if(g[i][my[i]] >= 1000) ans++;
    if(to[i] && my[i] != to[i]) be++;
  }
  printf("%d %d\n", ans, be);
  for(int i = 1; i <= m; ++i) {
    printf("%d ", my[i]);
  }
  return 0;
}