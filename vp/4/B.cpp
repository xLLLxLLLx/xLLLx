#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 20;
struct E {
  int x, y;
} b[N];
struct data {
  int nt, to, id;
} a[N << 1];
int n, m, cnt = 0;
vector<int> d;
int head[N], us[N], f[N];
int g[N][LOG + 1], c[N], dep[N], mk[N];

void add(int x, int y, int id) {
  // printf("%d %d %d\n", x, y, id);
  a[++cnt].to = y;
  a[cnt].id = id;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

int find(int k) {
  return f[k] == k ? f[k] : f[k] = find(f[k]);
}

void pre() {
  for(int i = 1; i <= n; ++i) f[i] = i;
  for(int i = 1; i <= m; ++i) {
    int fx = find(b[i].x), fy = find(b[i].y);
    if(fx != fy) {
      add(b[i].x, b[i].y, i), add(b[i].y, b[i].x, i);
      us[i] = 1;
      f[fx] = fy;
    }
  }
}

void dfs(int u, int fa) {
  g[u][0] = fa, dep[u] = dep[fa] + 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    mk[to] = a[i].id;
    dfs(to, u);
  }
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
    if(g[B][i] != g[A][i])
      B = g[B][i], A = g[A][i];
  return g[A][0];
}

void get(int u, int fa) {
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    get(to, u);
    c[u] += c[to];
  }
}

int main() {
  freopen("bridges.in", "r", stdin);
  freopen("bridges.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &b[i].x, &b[i].y);
  }
  pre(), dfs(1, 0), init();
  for(int i = 1; i <= m; ++i) {
    if(!us[i]) {
      int lca = GetLCA(b[i].x, b[i].y);
      c[b[i].x]++, c[b[i].y]++, c[lca] -= 2;
    }
  }
  get(1, 0);
  for(int i = 1; i <= n; ++i) {
    if(!c[i] && mk[i]) {
      d.push_back(mk[i]);
    }
  }
  printf("%d\n", (int)d.size());
  for(int i = 0; i < d.size(); ++i)
    printf("%d ", d[i]);
  return 0;
}