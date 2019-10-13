#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
struct data {
  int nt, to;
} a[N << 1];
int n, tp;
int head[N], sz[N], cnt = 0;
bitset<N> s;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void predfs(int u, int fa) {
  sz[u] = 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    predfs(to, u);
    sz[u] += sz[to];
  }
}

int vis[N];
void dfs(int u, int fa) {
  vector<int> g;
  g.push_back(n - sz[u]);
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    g.push_back(sz[to]);
    dfs(to, u);
  }
  for(int i = 1; i <= n - 2; ++i) s[i] = 0;
  s[0] = 1;
  for(int i = 0; i < g.size(); ++i) s |= (s << g[i]);
  for(int i = 1; i <= n - 2; ++i) if(s[i]) vis[i] = 1;
}

int main() {
  cin >> n >> tp;
  for(int i = 2, x, y; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  predfs(1, 0);
  dfs(1, 0);
  int ans = 0;
  for(int i = 1; i <= n - 2; ++i) if(vis[i]) ans++;
  printf("%d\n", ans);
  for(int i = 1; i <= n - 2; ++i)
    if(vis[i]) printf("%d %d\n", i, n - i - 1);
  return 0;
}