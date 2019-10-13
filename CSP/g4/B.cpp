#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
  int nt, to;
} a[N << 1];
map<int, int> mp[N], nm[N];
map<int, int> :: iterator sit;
vector<int> g[N];
int d[N], q[N], col[N], sz[N];
int head[N], cnt = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void merge(int x, int y) {
  if(sz[x] < sz[y]) mp[x].swap(mp[y]), nm[x].swap(nm[y]);
  sz[x] += sz[y];
  for(sit = mp[y].begin(); sit != mp[y].end(); ++sit) {
    int tmp = sit->first, pos = sit->second;
    while(pos) {
      mp[x][tmp]++;
      nm[x][mp[x][tmp]]++;
      pos--;
    }
  }
}

void dfs(int u, int fa) {
  sz[u] = 1;
  mp[u][col[u]]++, nm[u][mp[u][col[u]]]++;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) {
      continue;
    }
    dfs(to, u);
    merge(u, to);
  }
  // printf("now = %d\n", u);
  for(sit = mp[u].begin(); sit != mp[u].end(); ++sit)
    // printf("qwq%d %d\n", sit->first, sit->second);
  for(int i = 0; i < g[u].size(); ++i) {
    d[g[u][i]] = nm[u][q[g[u][i]]];
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i)
    scanf("%d", &col[i]);
  for(int i = 2, x, y; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  // puts("xxx");
  for(int i = 1, x; i <= m; ++i) {
    scanf("%d%d", &x, &q[i]);
    g[x].push_back(i);
  }
  // puts("XXX");
  dfs(1, 0);
  for(int i = 1; i <= m; ++i) {
    printf("%d\n", d[i]);
  }
  return 0;
}