#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
vector<int> g[N], c[N];
int f[N], d[N], v[N];

int find(int k) {
  return f[k] == k ? f[k] : f[k] = find(f[k]);
}

void dfs(int u, int val) {
  d[u] = v[u] + val;
  int pos = d[u];
  for(int i = 1; i < g[u].size(); ++i) {
    pos += c[u][i];
    dfs(g[u][i], pos);
  }
}

int main() {
  int n, q;
  cin >> n >> q;
  for(int i = 1; i <= n; ++i) {
    f[i] = i;
    g[i].push_back(0);
    c[i].push_back(0), c[i].push_back(0);
  }
  for(int o = 1; o <= q; ++o) {
    int tp, x, y;
    scanf("%d%d%d", &tp, &x, &y);
    if(tp == 1) {
      int fx = find(x), fy = find(y);
      if(fx == fy) {
        continue;
      } else {
        g[fy].push_back(fx);
        f[fx] = fy;
        c[fy].push_back(0);
      }
    } else {
      int fx = find(x);
      v[fx] += y;
      int len = g[fx].size();
      c[fx][len] -= y;
    }
  }
  /*for(int i = 1; i <= n; ++i) {
    printf("v[%d] = %d\n", i, v[i]);
    for(int j = 1; j < g[i].size(); ++j) {
      printf("%d ", g[i][j]);
    }
    puts("");
    for(int j = 1; j < g[i].size(); ++j)
      printf("%d ", c[i][j]);
    puts("");
  }*/
  for(int i = 1; i <= n; ++i) {
    if(find(i) == i) {
      dfs(i, 0);
    }
  }
  for(int i = 1; i <= n; ++i) {
    printf("%d ", d[i]);
  }
  puts("");
  return 0;
}