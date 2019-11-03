#include <bits/stdc++.h>
using namespace std;
const int N = 301, LOG = 9, mod = 1e9 + 7;
int n, m;
int r[N], a[N], b[N], c[N], X[N];

void read(int &x) {
  char ch = getchar(); x = 0;
  for(; ch < '0' || ch > '9'; ch = getchar()) ;
  for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

int jf(int x, int y) {
  return (x += y) >= mod ? x - mod : x;
}

int sub(int x, int y) {
  return (x -= y) < 0 ? x + mod : x;
}

void Add(int &x, int y) {
  x = jf(x, y);
}

struct Tree {
  int vs[N], tag[N], id[N], ou[N << 1];
  int nt[N << 1], to[N << 1], head[N], st[N << 1][LOG + 1], dep[N], cnt;
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
    ou[++ou[0]] = u, id[u] = ou[0];
    for(int i = head[u]; i; i = nt[i]) {
      if(to[i] == fa) continue;
      predfs(to[i], u);
      ou[++ou[0]] = u;
    }
  }
  void pre() {
    for(int i = 1; i <= ou[0]; ++i) st[i][0] = ou[i];
    for(int j = 1; j <= LOG; ++j)
      for(int i = 1; i <= ou[0]; ++i) {
        if(i + (1 << j) > ou[0] + 1) continue;
        st[i][j] = Min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
  }
  int Min(int x, int y) {
    return dep[x] >= dep[y] ? y : x;
  }
  int GetLCA(int l, int r) {
    l = id[l], r = id[r];
    if(l > r) swap(l, r);
    int k = (int)(log(double(r - l + 1)) / log(2.0));
    return Min(st[l][k], st[r - (1 << k) + 1][k]);
  }
  void dfs(int u, int fa) {
    for(int i = head[u]; i; i = nt[i]) {
      if(to[i] == fa) continue;
      dfs(to[i], u);
      Add(tag[u], tag[to[i]]);
      vs[i / 2] = tag[to[i]];
    }
  }
  void fg(int u, int v, int w) {
    int lca = GetLCA(u, v);
    // printf("qwq%d %d %d\n", u, v, lca);
    Add(tag[u], w), Add(tag[v], w), Add(tag[lca], sub(mod, 2ll * w % mod));
    // dfs(1, 0);
  }
  void clear() {
    memset(vs, 0, sizeof vs);
    memset(tag, 0, sizeof tag);
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
  read(n), read(m);
  for(int i = 1; i <= m; ++i) {
    // scanf("%d", &r[i]);
    read(r[i]);
  }
  for(int i = 1; i <= m; ++i) {
    // scanf("%d", &a[i]);
    read(a[i]);
  }
  for(int i = 1; i <= m; ++i) {
    // scanf("%d", &b[i]);
    read(b[i]);
  }
  for(int i = 1; i <= m; ++i) {
    // scanf("%d", &c[i]);
    read(c[i]);
  }
  for(int i = 1; i <= m; ++i) {
    get(i);
    tr[i].predfs(1, 0);
    tr[i].pre();
  }
}

int f[2][N][N];

int main() {
  init();
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
        tr[i].fg(u, v, f[now ^ 1][j][k]);
      }
      tr[i].dfs(1, 0);
      for(int t = 1; t < n; ++t)
        f[now][j][t] = tr[i].vs[t];
      tr[i].clear();
    }
    /*for(int j = 1; j < n; ++j)
      for(int k = 1; k < n; ++k)
        printf("f[%d][%d][%d] = %d\n", i, j, k, f[now][j][k]);*/
  }
  int ans = 0;
  for(int i = 1; i < n; ++i)
    for(int j = 1; j < n; ++j) {
      int u = tr[m].to[j * 2], v = tr[m].to[j * 2 + 1];
      tr[1].fg(u, v, 1);
      // gao(1, a[n][j * 2].to, a[n][j * 2 - 1].to);
      tr[1].dfs(1, 0);
      if(tr[1].vs[i]) 
        Add(ans, f[now][i][j]);
      tr[1].clear();
      // memset(vs, 0, sizeof vs);
    }
  printf("%d\n", ans);
  return 0;
}