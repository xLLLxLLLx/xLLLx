#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
struct data {
  int nt, to, w;
} a[N << 1];
ll ans = 0;
int head[N], sz[N];
int n, cnt = 0;

void add(int x, int y, int w) {
  a[++cnt].to = y;
  a[cnt].w = w;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void dfs(int u, int fa) {
  sz[u] = 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) {
      continue;
    }
    dfs(to, u);
    ans += 1ll * a[i].w * abs(n - 2 * sz[to]);
    sz[u] += sz[to];
  }
}

int main() {
  scanf("%d", &n);
  for(int i = 1, x, y, z; i < n; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    add(x, y, z), add(y, x, z);
  }
  dfs(1, 0);
  printf("%lld\n", ans);
  return 0;
}