#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, LOG = 20;
struct data {
  int nt, to;
} a[N << 1];
int st[N], ed[N], res = 0;
int head[N], g[N][LOG + 1], dep[N];
int n, cnt = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void dfs(int u, int fa) {
  st[u] = ++res;
  g[u][0] = fa;
  dep[u] = dep[fa] + 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    dfs(to, u);
  }
  ed[u] = res;
}

void init() {
  for(int j = 1; j <= LOG; ++j)
    for(int i = 1; i <= n; ++i)
      g[i][j] = g[g[i][j - 1]][j - 1];
}

int GetLCA(int A, int B) {
  if(dep[A] > dep[B]) swap(A, B);
  for(int i = LOG; i >= 0; --i)
    if(dep[g[B][i]] >= dep[A]) B = g[B][i];
  if(A == B) return A;
  for(int i = LOG; i >= 0; --i)
    if(g[A][i] != g[B][i])
      A = g[A][i], B = g[B][i];
  return g[A][0];
}

int Min(int x, int y) {
  if(x == -1) return y;
  return dep[x] > dep[y] ? y : x;
}

int up[N][LOG + 1];
void predfs(int u, int fa) {
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    for(int j = 0; j <= LOG; ++j) {
      if(up[to][j] && dep[up[to][j]] <= dep[u]) 
        up[u][j] = Min(up[u][j], up[to][j]);
    }
  }
}

int tr[N];
int lower(int x) {
  return x & (-x);
}

void upd(int x, int k) {
  for(; x < N; x += lower(x))
    tr[x] += k;
}

int get(int x) {
  int ans = 0;
  for(; x; x -= lower(x))
    ans += tr[x];
  return ans;
}

int main() {
  scanf("%d", &n);
  for(int i = 2, x, y; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  dfs(1, 0), init();
  int m;
  scanf("%d", &m);
  for(int o = 1, x, y; o <= m; ++o) {
    scanf("%d%d", &x, &y);
    int lca = GetLCA(x, y);
    up[u][0] = Min(up[u][0], lca);
  }
  predfs(1, 0);
  int q;
  scanf("%d", &q);
  for(int o = 1, x, y; o <= q; ++o) {
    scanf("%d%d", &x, &y);
    
  }
  return 0;
}