#include <bits/stdc++.h>
using namespace std;
const int N = 310, LOG = 10, mod = 1e9 + 7;
int n, m;
int r[N], a[N], b[N], c[N], X[N];

struct Tree {
  int vs[N], tag[N];
  int nt[N << 1], to[N << 1], head[N], g[N][LOG + 1], dep[N], cnt;
  Tree() {
    cnt = 1;
  }
  void add(int x, int y) {
    to[++cnt] = y;
    nt[cnt] = head[x];
    head[x] = cnt;
  }
  void predfs(int u, int fa) {
    dep[u] = dep[fa] + 1;
    g[u][0] = fa;
    for(int i = 1; i <= LOG; ++i) g[u][i] = g[g[u][i - 1]][i - 1];
    for(int i = head[u]; i; i = nt[i]) {
      if(to[i] == fa) continue;
      predfs(to[i], u);
    }
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
  void dfs(int u, int fa) {
    for(int i = head[u]; i; i = nt[i]) {
      if(to[i] == fa) continue;
      dfs(to[i], u);
      tag[u] += tag[to[i]];
      if(tag[to[i]]) vs[i / 2] = 1;
    }
  }
  void fg(int u, int v) {
    memset(vs, 0, sizeof vs), memset(tag, 0, sizeof tag);
    int lca = GetLCA(u, v);
    // printf("qwq%d %d %d\n", u, v, lca);
    tag[u]++, tag[v]++, tag[lca] -= 2;
    dfs(1, 0);
  }
} tr[N];

void get(int i) {
  // printf("root = %d\n", i);
  X[0] = c[i];
  for(int k = 1; k <= n - 2; ++k) 
    X[k] = (1ll * a[i] * X[k - 1] % mod + b[i]) % mod;
  for(int j = 0; j <= n - 2; ++j) {
    int u = (r[i] + j + 1) % n + 1;
    int v = (r[i] + (X[j] % (j + 1))) % n + 1;
    // printf("%d %d\n", u, v);
    tr[i].add(u, v), tr[i].add(v, u);
  }
}

void init() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; ++i) {
    scanf("%d", &r[i]);
  }
  for(int i = 1; i <= m; ++i) {
    scanf("%d", &a[i]);
  }
  for(int i = 1; i <= m; ++i) {
    scanf("%d", &b[i]);
  }
  for(int i = 1; i <= m; ++i) {
    scanf("%d", &c[i]);
  }
  for(int i = 1; i <= m; ++i) {
    get(i);
    tr[i].predfs(1, 0);
  }
}

int jf(int x, int y) {
  return (x += y) > mod ? x - mod : x;
}

void Add(int &x, int y) {
  x = jf(x, y);
}

int f[2][N][N];

int main() {
  init();
  memset(f, 0, sizeof f);
  int now = 0;
  {
    for(int i = 1; i < n; ++i) {
      f[now][i][i] = 1;
    }
  }
  for(int i = 2; i <= m; ++i){
    now ^= 1;
    memset(f[now], 0, sizeof f[now]);
    for(int j = 1; j < n; ++j) {
      for(int k = 1; k < n; ++k) {
        if(!f[now ^ 1][j][k]) continue;
        int u = tr[i - 1].to[k * 2], v = tr[i - 1].to[k * 2 + 1];
        // printf("%d %d\n", u, v);
        tr[i].fg(u, v);
        for(int t = 1; t < n; ++t) {
          if(tr[i].vs[t])
            Add(f[now][j][t], f[now ^ 1][j][k]);
        }
        // memset(vs, 0, sizeof vs);
      }
      /*for(int k = 1; k < n; ++k) {
        printf("f[%d][%d][%d] = %d\n", i, j, k, f[now][j][k]);
      }*/
    }
    /*for(int j = 1; j < n; ++j)
      for(int k = 1; k < n; ++k)
        printf("f[%d][%d][%d] = %d\n", i, j, k, f[now][j][k]);*/
  }
  int ans = 0;
  for(int i = 1; i < n; ++i)
    for(int j = 1; j < n; ++j) {
      int u = tr[m].to[j * 2], v = tr[m].to[j * 2 + 1];
      tr[1].fg(u, v);
      // gao(1, a[n][j * 2].to, a[n][j * 2 - 1].to);
      if(tr[1].vs[i]) 
        Add(ans, f[now][i][j]);
      // memset(vs, 0, sizeof vs);
    }
  printf("%d\n", ans);
  return 0;
}