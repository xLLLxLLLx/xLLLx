#include <bits/stdc++.h>
using namespace std;
const int N = 6e5 + 10, LOG = 20;
struct data {
  int nt, to, w;
} a[N << 1], b[N];
int g[N][LOG + 1], dep[N], vis[N];
int cnt = 0, now, head[N], val[N];

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

int n, m, q;
bool cmp(data A, data B) {
  return A.w < B.w;
}

int f[N];
int find(int k) {
  return f[k] == k ? f[k] : f[k] = find(f[k]);
}

void kruskal() {
  now = n;
  sort(b + 1, b + 1 + m, cmp);
  for(int i = 1; i <= n * 2; ++i)
    f[i] = i;
  for(int i = 1; i <= m; ++i) {
    int fx = find(b[i].nt), fy = find(b[i].to);
    if(fx != fy) {
      ++now;
      add(now, fx), add(now, fy);
      val[now] = b[i].w;
      f[fx] = f[fy] = now;
    }
  }
}

void dfs(int u, int fa) {
  vis[u] = 1;
  g[u][0] = fa, dep[u] = dep[fa] + 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    dfs(to, u);
  }
}

void go() {
  for(int j = 1; j <= LOG; ++j)
    for(int i = 1; i <= now; ++i)
      g[i][j] = g[g[i][j - 1]][j - 1];
  // for(int i = 1; i <=  now; ++i)
  //   for(int j = 0; j <= LOG; ++j)
  //     if(g[i][j]) printf("g[%d][%d]=%d\n", i, j, g[i][j]);
}

int GetLCA(int A, int B) {
  if(dep[A] > dep[B]) swap(A, B);
  for(int i = LOG; i >= 0; --i)
    if(dep[g[B][i]] >= dep[A])
      B = g[B][i];
  if(A == B) return A;
  for(int i = LOG; i >= 0; --i)
    if(g[B][i] != g[A][i])
      B = g[B][i], A = g[A][i];
  return g[A][0];
}

int main() {
  //freopen("out", "r", stdin);
  scanf("%d%d%d", &n, &m, &q);
  for(int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &b[i].nt, &b[i].to, &b[i].w);
  }
  kruskal();
  for(int i = now; i >= 1; --i) {
    if(!vis[i]) dfs(i, 0);
  }
  go();
  for(int i = 1, x, y; i <= q; ++i) {
    scanf("%d%d", &x, &y);
    if(find(x) != find(y)) {
      printf("-1\n");
    } else {
      printf("%d\n", val[GetLCA(x, y)]);
    }
  }
  return 0;
}