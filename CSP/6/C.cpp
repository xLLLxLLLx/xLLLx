#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10, LOG = 20;
struct data {
  int fr, nt, to;
} a[N << 1];
int head[N], dep[N];
int ou[N << 1], ys[N], st[N << 1][LOG + 1], cnt = 1, res = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].fr = x;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void predfs(int u, int fa) {
  dep[u] = dep[fa] + 1;
  ou[++res] = u, ys[u] = res;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    predfs(to, u);
    ou[++res] = u;
  }
}

int Min(int x, int y) {
  return dep[x] > dep[y] ? y : x;
}

void init() {
  for(int i = 1; i <= res; ++i) st[i][0] = ou[i];
  for(int j = 1; j <= LOG; ++j)
    for(int i = 1; i <= res; ++i) {
      if(i + (1 << j) > res + 1) continue;
      st[i][j] = Min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
}

int GetLCA(int l, int r) {
  l = ys[l], r = ys[r];
  if(l > r) swap(l, r);
  int k = (int)(log(double(r - l + 1)) / log(2.0));
  return Min(st[l][k], st[r - (1 << k) + 1][k]);
}

int getdis(int x, int y) {
  int lca = GetLCA(x, y);
  return dep[x] + dep[y] - 2 * dep[lca];
}

int f[N], p[N][2], d[N];
int find(int k) {
  return f[k] == k ? f[k] : f[k] = find(f[k]);
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 2, x, y; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  predfs(1, 0), init();
  for(int i = 1; i <= n; ++i) f[i] = i, p[i][0] = p[i][1] = i;
  for(int i = 1; i < n; ++i) {
    int x = a[i * 2].fr, y = a[i * 2].to;
    int fx = find(x), fy = find(y);
    // printf("x = %d y = %d\n", x, y);
    int ans = 0, bx, by;
    if(d[fx] >= d[fy]) {
      ans = d[fx];
      bx = p[fx][0], by = p[fx][1];
    } else {
      ans = d[fy];
      bx = p[fy][0], by = p[fy][1];
    }
    for(int j = 0; j < 2; ++j)
      for(int k = 0; k < 2; ++k) {
        int pos = getdis(p[fx][j], p[fy][k]);
        if(pos >= ans) {
          ans = pos;
          bx = p[fx][j], by = p[fy][k];
        }
      }
    printf("%d\n", ans);
    // printf("%d %d\n", bx, by);
    f[fx] = fy, d[fy] = ans;
    p[fy][0] = bx, p[fy][1] = by;
  }
  return 0;
}