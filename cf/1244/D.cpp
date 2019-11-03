#include <bits/stdc++.h>
#define ll long long
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data {
  int nt, to;
} a[N << 1];
int pr[N][3][3][2];
int d[N], head[N], c[N], cnt = 0;
ll f[N][3][3], w[3][N];

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void go(int x, int fi, int se) {
  if(!x) return ;
  c[x] = fi + 1;
  go(pr[x][fi][se][0], se, pr[x][fi][se][1]);
}

void dfs(int u, int fa) {
  int flg = 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    dfs(to, u);
    for(int j = 0; j < 3; ++j)
      for(int k = 0; k < 3; ++k) {
        int gg = 7;
        gg ^= ((1 << j) | (1 << k));
        for(int t = 0; t < 3; ++t){
          if(gg & (1 << t)) {
            //f[to][j][k]->f[u][t][j]
            if(f[u][t][j] > f[to][j][k] + w[t][u]) {
              // printf("u = %d %d %d %d to = %d %lld\n", u, t, j, k, to, f[to][j][k]);
              f[u][t][j] = f[to][j][k] + w[t][u];
              // if(u == 2 && t == 0 && j == 0) printf("QWQW%lld\n", f[u][j][k]);
              pr[u][t][j][0] = to, pr[u][t][j][1] = k;
            }
          }
        }
      }
    flg = 0;
  }
  if(flg) {
    for(int i = 0; i < 3; ++i)
      f[u][i][i] = w[i][u];
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i < 3; ++i)
    for(int j = 1; j <= n; ++j)
      scanf("%lld", &w[i][j]);
  for(int i = 2, x, y; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
    d[x]++, d[y]++;
  }
  int mx = 0, be = 0;
  for(int i = 1; i <= n; ++i) {
    if(d[i] == 1) be = i;
    mx = max(mx, d[i]);
  }
  if(mx > 2) puts("-1");
  else {
    memset(f, 0x3f, sizeof f);
    dfs(be, 0);
    ll ans = 1e18;
    int x = 0, y = 0;
    for(int i = 0; i < 3; ++i)
      for(int j = 0; j < 3; ++j)
        if(ans > f[be][i][j]) {
          ans = f[be][i][j];
          x = i, y = j;
        }
    go(be, x, y);
    printf("%lld\n", ans);
    for(int i = 1; i <= n; ++i)
      printf("%d ", c[i]);
  }
  return 0;
}