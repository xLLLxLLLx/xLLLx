#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
struct data {
  int nt, to;
} a[N << 1];
int head[N], vis[N], cnt = 1;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

int ans = 0, d[N][N], vs[N], mk[2050];
void dfs(int now, int mask, int ed) {
  if(now == ed) {
    if(!mk[mask]) mk[mask] = 1, ans++;
    return ;
  }
  for(int i = head[now]; i; i = a[i].nt) {
    int to = a[i].to;
    if(vs[i >> 1]) continue;
    vs[i >> 1] = 1;
    dfs(to, mask | (1 << ((i >> 1) - 1)), ed);
    vs[i >> 1] = 0;
  }
}

int n, m;
void init() {
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      ans = 0;
      memset(mk, 0, sizeof mk);
      dfs(i, 0, j);
      d[i][j] = ans;
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  init();
  int q;
  scanf("%d", &q);
  for(int o = 1, x, y; o <= q; ++o) {
    scanf("%d%d", &x, &y);
    printf("%d\n", d[x][y]);
  }
  return 0;
}