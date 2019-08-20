#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010;
ll a[N], c[N], b[N], f[N][N], pr[N][N];

template <class T>
void read(T & x) {
  char ch = getchar(); x = 0;
  for(; ch < '0' || ch > '9'; ch = getchar()) ;
  for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

void Min(ll &x, ll y) {
  if(x == -1) x = y;
  else x = min(x, y);
}

void go(int x, int y) {
  if(!x) return ;
  int pos = pr[x][y];
  if(pos == y - 1) {
    go(x - 1, pos);
    printf("%d ", c[x] + 1);
  } else if(pos == y) {
    go(x - 1, pos);
    printf("%d ", c[x]);
  }
}

int main() {
  freopen("robbers.in", "r", stdin);
  freopen("robbers.out", "w", stdout);
  int n;
  ll m, y, res = 0;
  read(n), read(m), read(y);
  memset(f, -1, sizeof f);
  f[0][0] = 0;
  for(int i = 1; i <= n; ++i) {
    read(a[i]);
    c[i] = a[i] * m / y;
    b[i] = a[i] * m - c[i] * y;
    f[0][0] += b[i];
    res += c[i];
  }  
  int yu = m - res;
  for(int i = 1; i <= n; ++i) {
    for(int j = 0; j <= min(yu, i); ++j) {
      if(f[i - 1][j] == -1) continue;
      Min(f[i][j], f[i - 1][j]);
      if(f[i][j] == f[i - 1][j]) {
        pr[i][j] = j;
      }
      int pos = f[i - 1][j] + (y - 2 * b[i]);
      Min(f[i][j + 1], pos);
      if(f[i][j + 1] == pos) pr[i][j + 1] = j;
    }
  }
  // printf("%d\n", f[n][yu]);
  go(n, yu);
  return 0;
}