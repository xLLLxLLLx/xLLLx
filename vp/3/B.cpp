#include <bits/stdc++.h>
using namespace std;
const int N = 410, inf = 1e9;
struct data {
  int nt, to;
} a[N * N];
int mx[N], my[N], vx[N], vy[N], lx[N], ly[N], g[N][N];
int head[N], cnt = 0, yu;
int n;

bool dfs(int u) {
  // printf("u=%d\n", u);
  vx[u] = 1;
  for(int i = 1; i <= n; ++i) {
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
  freopen("beloved.in", "r", stdin);
  freopen("beloved.out", "w", stdout);
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &lx[i]);
    lx[i] *= lx[i];
  }
  for(int i = 1, num; i <= n; ++i) {
    scanf("%d", &num);
    for(int j = 1, x; j <= num; ++j) {
      scanf("%d", &x);
      g[i][x] = lx[i];
    }
  }
  for(int i = 1; i <= n; ++i) {
    // printf("%d\n", i);
    for(;;) {
      memset(vx, 0, sizeof vx);
      memset(vy, 0, sizeof vy);
      yu = inf;
      if(dfs(i)) break;
      for(int i = 1; i <= n; ++i) {
        if(vx[i]) lx[i] -= yu;
        if(vy[i]) ly[i] += yu;
      }
    }
  }
  for(int i = 1; i <= n; ++i) {
    if(g[i][my[i]]) printf("%d ", my[i]);
    else printf("0 ");
  }
  return 0;
}