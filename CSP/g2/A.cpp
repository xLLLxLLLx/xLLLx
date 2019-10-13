#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int ans = 0;
int vs[N], L[N], f[N];
vector<int> g[N];

void dfs(int u, int be, int l) {
  if(u == be) {
    ans = max(ans, l);
    return ;
  }
  if(vs[u]) return ;
  vs[u] = 1;
  dfs(f[u], be, l + 1);
}

void dfs(int u, int fa, int l, int be) {
  L[be] = max(L[be], l);
  for(int i = 0; i < (int)g[u].size(); ++i) {
    int to = g[u][i];
    if(to == fa) continue;
    dfs(to, u, l + 1, be);
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int n;
    scanf("%d", &n);
    ans = 0;
    for(int i = 1; i <= n; ++i) {
      g[i].clear();
    }
    for(int i = 1; i <= n; ++i) {
      scanf("%d", &f[i]);
      g[f[i]].push_back(i);
      g[i].push_back(f[i]);
    }
    for(int i = 1; i <= n; ++i) {
      vs[i] = 1;
      dfs(f[i], i, 1);
      memset(vs, 0, sizeof vs);
    }
    // printf("%d\n", ans);
    int pos = 0;
    memset(L, -1, sizeof L);
    for(int i = 1; i <= n; ++i) {
      if(f[f[i]] == i) {
        dfs(i, f[i], 0, i);
        pos += 1 + L[i];
        // printf("%d\n", L[i]);
      }
    }
    ans = max(ans, pos);
    printf("Case #%d: %d\n", o, ans);
  }
  return 0;
}