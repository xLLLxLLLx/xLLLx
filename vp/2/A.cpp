#include <bits/stdc++.h>
using namespace std;
const int N = 1010, mod = 100000000;
int m, n, S, t, len;
int a[N][N], b[N][N], vs[N], us[N];
char lx[N];

int c[N];
void add(int a[], int b[]) {
  c[0] = max(a[0], b[0]) + 1;
  for(int i = 1; i <= c[0]; ++i) {
    c[i] = a[i] + b[i];
  }
  for(int i = 1; i <= c[0]; ++i) {
    c[i + 1] += c[i] / mod;
    c[i] %= mod;
  }
  while(c[0] > 1 && !c[c[0]]) --c[0];
  for(int i = 0; i <= c[0]; ++i)
    a[i] = c[i];
}

void print(int a[]) {
  printf("%d", a[a[0]]);
  for(int i = a[0] - 1; i >= 1; --i) {
    printf("%08d", a[i]);
  }
  puts("");
}

void dfs(int x, int y) {
  us[x] = 1;
  int pos = a[x][y];
  if(b[pos][y] && !us[pos]) dfs(pos, y);
  if(!b[pos][y]) a[x][y] = a[pos][y], b[x][y] = 0;
}

void init() {
  for(int j = 0; j < m; ++j) {
    memset(us, 0, sizeof us);
    for(int i = 1; i <= n; ++i) {
      if(b[i][j] && !us[i]) 
        dfs(i, j);
    }
  }
}

int f[N][70][110], ans[N];

int main() {
  freopen("dfa.in", "r", stdin);
  freopen("dfa.out", "w", stdout);
  scanf("%s", lx + 1);
  m = strlen(lx + 1);
  scanf("%d%d%d", &n, &S, &t);
  for(int i = 1, x; i <= t; ++i) {
    scanf("%d", &x);
    vs[x] = 1;
  }
  for(int i = 1; i <= n; ++i)
    for(int j = 0; j < m; ++j) {
      scanf("%d", &a[i][j]);
    }
  for(int i = 1; i <= n; ++i)
    for(int j = 0; j < m; ++j) {
      scanf("%d", &b[i][j]);
    }
  scanf("%d", &len);
  init();
  f[S][0][0] = f[S][0][1] = 1;
  for(int k = 0; k <= len; ++k) 
    for(int i = 1; i <= n; ++i) 
      for(int j = 0; j < m; ++j) {
        if(!b[i][j])
          add(f[a[i][j]][k + 1], f[i][k]);
      }
  for(int i = 1; i <= n; ++i)
    if(vs[i]) add(ans, f[i][len]);
  print(ans);
  return 0;
}