#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int nm[N], f[N], sz[N], g[N];

int find(int k) {
  return f[k] == k ? f[k] : f[k] = find(f[k]);
}

int res = 0;
int w[N], v[N];

bool check(int x) {
  for(; x; x /= 10) {
    int pos = x % 10;
    if(pos != 4 && pos != 7) return false;
  }
  return true;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int n, m;
    scanf("%d%d", &n, &m);
    res = 0;
    for(int i = 1; i <= n; ++i) nm[i] = 0, f[i] = i, sz[i] = 1;
    for(int i = 1, x, y; i <= m; ++i) {
      scanf("%d%d", &x, &y);
      int fx = find(x), fy = find(y);
      if(fx == fy) continue;
      f[fx] = fy;
      sz[fy] += sz[fx];
    }
    for(int i = 1; i <= n; ++i) {
      if(find(i) == i) nm[sz[i]]++;
    }
    int ans = 1e9;
    for(int i = 1; i <= n; ++i) {
      if(nm[i]) {
        int pos = nm[i];
        for(int j = 1; ; j <<= 1) {
          if(pos > j) {
            pos -= j;
            w[++res] = i * j, v[res] = j;
          } else {
            w[++res] = i * pos, v[res] = pos;
            break;
          }
        }
      }
    }
    /*for(int i = 1; i <= res; ++i)
      printf("%d %d\n", w[i], v[i]);*/
    memset(g, 0x3f, sizeof g);
    g[0] = 0;
    for(int i = 1; i <= res; ++i)
      for(int j = n; j >= w[i]; --j) {
        g[j] = min(g[j], g[j - w[i]] + v[i]);
      }
    for(int i = 1; i <= n; ++i) {
      if(check(i)) ans = min(ans, g[i]);
    }
    if(ans <= n) printf("%d\n", ans - 1);
    else puts("-1");
  }
  return 0;
}