#include <bits/stdc++.h>
using namespace std;
const int N = 410, inf = 1e9;
struct data {
  int nt, to, w;
} a[N << 1];
int g[N][N], lx[N], mx[N], ly[N], vx[N], vy[N];
int head[N], c[N];
int cnt = 1, tot, yu;

void add(int x, int y, int w) {
  a[++cnt].to = y;
  a[cnt].w = w;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

bool cal(int u, int fa, int v, int id, int w) {
  if(u == v) return true;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa || !cal(to, u, v, id, w)) {
      continue;
    }
    g[i >> 1][id] = max(g[i >> 1][id], a[i].w - w);
    return true;
  }
  return false;
}

bool dfs(int u) {
  vx[u] = 1;
  int pos = 0;
  for(int i = 1; i <= tot; ++i) {
    if(!vy[i]) {
      pos = lx[u] + ly[i] - g[u][i];
      if(!pos) {
        vy[i] = 1;
        if(!mx[i] || dfs(mx[i])) {
          mx[i] = u;
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
  freopen("roads.in", "r", stdin);
  freopen("roads.out", "w", stdout);
  int n, m;
  scanf("%d%d", &n, &m);
  n--;
  m -= n;
  for(int i = 1, x, y, w; i <= n; ++i) {
    scanf("%d%d%d", &x, &y, &w);
    add(x, y, w), add(y, x, w);
  }
  for(int i = 1, x, y, w; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &w);
    c[i] = w;
    cal(x, 0, y, i, w);
  }
  tot = max(n, m);
  for(int i = 1; i <= tot; ++i) 
    for(int j = 1; j <= tot; ++j)
      lx[i] = max(lx[i], g[i][j]);
  for(int o = 1; o <= tot; ++o) {
    // printf("%d\n", o);
    for(;;) {
      memset(vx, 0, sizeof vx);
      memset(vy, 0, sizeof vy);
      yu = inf;
      if(dfs(o)) break;
      for(int i = 1; i <= tot; ++i) {
        if(vx[i]) lx[i] -= yu;
        if(vy[i]) ly[i] += yu;
      }
    }
  }
  for(int i = 1; i <= n; ++i) {
    printf("%d\n", a[i << 1].w - lx[i]);
  }
  for(int i = 1; i <= m; ++i) {
    printf("%d\n", c[i] + ly[i]);
  }
  return 0;
}