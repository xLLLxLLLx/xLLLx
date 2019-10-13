#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10, LOG = 14;
struct data {
  int nt, to;
} a[N << 1];
int n;
int head[N], g[N][LOG + 1], dep[N], sz[N], cnt = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void dfs(int u, int fa) {
  sz[u] = 1;
  g[u][0] = fa, dep[u] = dep[fa] + 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    dfs(to, u);
    sz[u] += sz[to];
  }
}

void get() {
  for(int j = 1; j <= LOG; ++j)
    for(int i = 1; i <= n; ++i)
      g[i][j] = g[g[i][j - 1]][j - 1];
}

int GetLCA(int A, int B) {
  if(dep[A] > dep[B]) swap(A, B);
  for(int i = LOG; i >= 0; --i) {
    if(dep[g[B][i]] >= dep[A]) B = g[B][i];
  }
  if(A == B) return A;
  for(int i = LOG; i >= 0; --i)
    if(g[A][i] != g[B][i]) 
      A = g[A][i], B = g[B][i];
  return g[A][0];
}

int de[N], c[N], ys[N], s[3], p[3], d[N][3], ans[3];

void go(int u, int fa) {
  c[++c[0]] = u, ys[u] = c[0];
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    go(to, u);
  }
}

bool cmp(int x, int y) {
  return s[x] < s[y];
}

int main() {
  scanf("%d", &n);
  int F = 1;
  for(int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
    de[x]++, de[y]++;
    if(de[x] > 2 || de[y] > 2) F = 0;
  }
  dfs(1, 0), get();
  int q;
  scanf("%d", &q);
  if(n <= 1000) {
    for(int o = 1; o <= q; ++o) {
      memset(ans, 0, sizeof ans);
      for(int i = 0, x; i < 3; ++i) {
        scanf("%d", &x);
        for(int j = 1; j <= n; ++j) {
          d[j][i] = dep[x] + dep[j] - 2 * dep[GetLCA(x, j)];
          // printf("%d ", d[j][i]);
        }
        // puts("");
      }
      for(int i = 1; i <= n; ++i) {
        int be = 0, flg = 0, mx = n + 1;
        for(int j = 0; j < 3; ++j) {
          if(d[i][j] < mx) {
            mx = d[i][j];
            be = j;
            flg = 0;
          } else if(d[i][j] == mx) {
            flg = 1;
          }
        }
        if(!flg) ans[be]++;
      }
      for(int i = 0; i < 3; ++i) {
        printf("%d", ans[i]);
        if(i != 2) printf(" ");
      }
      puts("");
    }
  } 
  return 0;
}