#include <bits/stdc++.h>
using namespace std;
const int N = 25, M = (1 << 20);
int f[M], g[M], a[N][N];
char lx[N][N];

typedef pair<int, int> P;
#define fi first
#define se second
P v[N][N];

void Min(int &x, int y) {
  x = min(x, y);
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int tot = (1 << n) - 1;
  for(int i = 0; i < n; ++i) {
    scanf("%s", lx[i] + 1);
  }
  for(int i = 0; i < n; ++i)
    for(int j = 1; j <= m; ++j)
      scanf("%d", &a[i][j]);
  for(int i = 0; i < n; ++i) {
    for(int k = 1; k <= m; ++k) {
      int pos = 0, tmp = 0;
      for(int j = 0; j < n; ++j) {
        if(i == j) continue;
        if(lx[j][k] == lx[i][k])
          pos |= (1 << j), tmp += a[j][k];
      }
      v[i][k] = P(pos, tmp);
    }
  }
  /*for(int i = 0; i < n; ++i)
    for(int j = 1; j <= m; ++j)
      printf("i = %d %d %d\n", i, v[i][j].fi, v[i][j].se);*/
  memset(f, 0x3f, sizeof f);
  f[0] = 0;
  for(int i = 0; i < n; ++i) 
    for(int j = 0; j <= tot; ++j) {
      if((j >> i) & 1) continue;
      for(int t = 1; t <= m; ++t) {
        int mk = v[i][t].fi, w = v[i][t].se;
        if(!mk) Min(f[j | (1 << i)], f[j]);
        else {
          Min(f[j | (1 << i)], f[j] + a[i][t]);
          Min(f[j | (mk | (1 << i))], f[j] + w);
        }
      }
    }
  /*for(int i = 0; i <= tot; ++i)
    if(f[i] != f[100]) printf("f[%d] = %d\n", i, f[i]);*/
  printf("%d\n", f[tot]);
  return 0;
}