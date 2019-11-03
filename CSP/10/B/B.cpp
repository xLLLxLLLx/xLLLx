#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data {
  int nt, to, w;
} a[2][N << 1];
ll qz[N];
int dfn[N], low[N], res = 0, vis[N], stk[N], top = 0, col[N], num = 0;
int head[2][N], cnt[2];
int d[N];

void add(int id, int x, int y, int w) {
  if(id == 1) d[y]++;
  a[id][++cnt[id]].to = y;
  a[id][cnt[id]].w = w;
  a[id][cnt[id]].nt = head[id][x];
  head[id][x] = cnt[id];
}

void dfs(int u) {
  vis[u] = 1;
  dfn[u] = low[u] = ++res;
  stk[++top] = u;
  for(int i = head[0][u]; i; i = a[0][i].nt) {
    int to = a[0][i].to;
    if(!dfn[to]) {
      dfs(to);
      low[u] = min(low[u], low[to]);
    } else if(vis[to]) {
      low[u] = min(low[u], dfn[to]);
    }
  }
  if(dfn[u] == low[u]) {
    vis[u] = 0, col[u] = ++num;
    while(stk[top] != u) {
      vis[stk[top]] = 0;
      col[stk[top--]] = num;
    }
    top--;
  }
}

void init() {
  for(int i = 1; i < N; ++i)
    qz[i] = qz[i - 1] + 1ll * i * (i - 1) / 2;
}

int find(int x) {
  int l = 1, r = 1e5, ans = 0;
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(1ll * mid * (mid - 1) / 2 <= x) l = mid + 1, ans = mid;
    else r = mid - 1;
  }
  return ans;
}

ll get(int x) {
  int s = find(x);
  return 1ll * s * x - qz[s];
}

int vs[N];
ll val[N], zh[N], f[N];

void go(int u) {
  vs[u] = 1;
  f[u] = val[u];
  for(int i = head[1][u]; i; i = a[1][i].nt) {
    int to = a[1][i].to;
    go(to);
    f[u] = max(f[u], f[to] + a[1][i].w + val[u]);
  }
}

int main() {
  init();
  int n, m;
  scanf("%d%d", &n, &m);
  ll ans = 0;
  for(int i = 1, x, y, z; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    if(x == y) zh[x] += get(z);
    else add(0, x, y, z);
  }
  for(int i = 1; i <= n; ++i) {
    if(!dfn[i]) dfs(i);
  }
  for(int u = 1; u <= n; ++u) {
    val[col[u]] += zh[u];
    for(int i = head[0][u]; i; i = a[0][i].nt) {
      int to = a[0][i].to;
      if(col[to] == col[u]) val[col[u]] += get(a[0][i].w);
      else add(1, col[u], col[to], a[0][i].w);
    }
  }
  int s;
  scanf("%d", &s);
  f[col[s]] = val[col[s]];
  go(col[s]);
  for(int i = 1; i <= num; ++i) {
    ans = max(ans, f[i]);
  }
  printf("%lld\n", ans);
  return 0;
}