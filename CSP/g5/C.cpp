#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 20;
struct data {
  int nt, to;
} a[N << 1];
int n;
int g[N][LOG + 1], dep[N], sz[N], st[N], ed[N];
int head[N], cnt = 0, res = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void dfs(int u, int fa) {
  st[u] = ++res;
  sz[u] = 1;
  dep[u] = dep[fa] + 1, g[u][0] = fa;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    dfs(to, u);
    sz[u] += sz[to];
  }
  ed[u] = res;
}

void get() {
  for(int j = 1; j <= LOG; ++j)
    for(int i = 1; i <= n; ++i)
      g[i][j] = g[g[i][j - 1]][j - 1];
}

int GetLCA(int A, int B) {
  if(dep[A] > dep[B]) swap(A, B);
  for(int i = LOG; i >= 0; --i)
    if(dep[g[B][i]] >= dep[A])
      B = g[B][i];
  if(A == B) return A;
  for(int i = LOG; i >= 0; --i)
    if(g[A][i] != g[B][i])
      A = g[A][i], B = g[B][i];
  return g[A][0];
}

int get(int be, int dis) {
  // printf("qwq%d %d\n", be, dis);
  for(int i = LOG; i >= 0; --i) {
    if(dis >= (1 << i)) {
      dis -= (1 << i);
      be = g[be][i];
    }
  }
  // printf("be = %d\n", be);
  return be;
}

int cal(int x, int y, int z) {
  // printf("%d %d %d\n", x, y, z);
  int lca = GetLCA(x, y), dis = dep[x] + dep[y] - 2 * dep[lca];
  int mid1, mid2, p1 = 0, p2 = 0;
  if(dep[x] - dep[lca] >= dep[y] - dep[lca]) {
    p1 = 1;
    mid1 = get(x, (dis - 1) / 2);
  } else {
    p1 = 2;
    mid1 = get(y, dis / 2); //??
  }
  lca = GetLCA(x, z), dis = dep[x] + dep[z] - 2 * dep[lca];
  if(dep[x] - dep[lca] >= dep[z] - dep[lca]) {
    p2 = 1;
    mid2 = get(x, (dis - 1) / 2);
  } else {
    p2 = 2;
    // puts("xxX");
    mid2 = get(z, dis / 2); //??
  }
  // printf("qwq%d %d %d %d\n", mid1, mid2, p1, p2);
  if(p1 == 1 && p2 == 1) {
    if(dep[mid1] < dep[mid2]) swap(mid1, mid2), swap(p1, p2), swap(y, z);
    if(p1 == 2) {
      int pos = get(y, dep[lca] - dep[y] - 1);
      return sz[mid1] - sz[pos];
    } else return sz[mid1];
  } else if(p1 == 2 && p2 == 2) {
    if(dep[mid1] > dep[mid2]) swap(mid1, mid2);
    if(st[mid1] <= st[mid2] && st[mid2] <= ed[mid1]) return n - sz[mid1];
    else return n - sz[mid1] - sz[mid2];
  } else {
    if(p1 == 2) swap(mid1, mid2);
    if(st[mid1] <= st[mid2] && st[mid2] <= ed[mid1]) {
      return sz[mid1] - sz[mid2];
    } else {
      return sz[mid1];
    }
  }
}

int main() {
  scanf("%d", &n);
  for(int i = 2, x, y; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  dfs(1, 0), get();
  int q;
  scanf("%d", &q);
  // printf("%d\n", cal(4, 8, 8));
  for(int o = 1, x, y, z; o <= q; ++o) {
    scanf("%d%d%d", &x, &y, &z);
    printf("%d %d %d\n", cal(x, y, z), cal(y, x, z), cal(z, x, y));
  }
  return 0;
}