#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 10;
int vs[N][N], a[N][N];
char lx[N][N];

int n, m;
bool check() {
  int F = 0;
  for(int i = 0; i < n; ++i) {
    for(int k = 0; k < m; ++k) {
      int flg = 1;
      if(!vs[i][k]) {
        for(int j = 0; j < n; ++j) {
          if(i == j) continue;
          if(vs[j][k] || lx[j][k] != lx[i][k]) ;
          else {
            flg = 0;
            break;
          }
        }
      }
      if(flg) {
        F++;
        break;
      }
    }
  }
  return F == n;
}

int main() {
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; ++i)
    scanf("%s", lx[i]);
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j)
      scanf("%d", &a[i][j]);
  int tot = (1 << (n * m)) - 1;
  ll ans = 1e9;
  for(int i = 0; i <= tot; ++i) {
    ll pos = 0;
    for(int j = 0; j < (n * m); ++j) {
      if((i >> j) & 1) continue;
      int x = j / m, y = j % m;
      pos += a[x][y], vs[x][y] = 1;
    }
    if(check()) {
      // puts("xx");
      ans = min(ans, pos);
    }
    memset(vs, 0, sizeof vs);
  }
  printf("%lld\n", ans);
  return 0;
}