#include <bits/stdc++.h>
using namespace std;
const int N = 55, mod = 1e9 + 7;
int dp[N][N][N][N], a[N], pw[N];

int add(int x, int y) {
  return (x + y) % mod;
}

int mul(int x, int y) {
  return 1ll * x * y % mod;
}

void Add(int &x, int y) {
  x = add(x, y);
}

void Mul(int &x, int y) {
  x = mul(x, y);
}

void init() {
  pw[0] = 1;
  for(int i = 1; i < N; ++i)
    pw[i] = pw[i - 1] * 2 % mod;
}

int main() {
  init();
  int n, p;
  scanf("%d%d", &n, &p);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  dp[0][0][0][0] = 1;
  for(int i = 1; i <= n; ++i)
    for(int j = 0; j < i; ++j)
      for(int k = 0; k < i; ++k)
        for(int t = 0; t < i; ++t) {
          if(!dp[i - 1][j][k][t]) continue;
          int gg = dp[i - 1][j][k][t];
          int oh = i - j - k - t - 1;
          if(a[i] == -1) {
            // bai
            int tmp;
            if(t) tmp = i - 2;
            else tmp = i - 1;
            // printf("%d %d\n", tmp, pw[tmp]);
            Add(dp[i][j + 1][k][t], mul(gg, pw[tmp]));
            if(t) Add(dp[i][j][k + 1][t], mul(gg, pw[tmp]));
            // hei
            int pos;
            if(j) pos = i - 2;
            else pos = i - 1;
            Add(dp[i][j][k][t + 1], mul(gg, pw[pos]));
            if(j) Add(dp[i][j][k][t], mul(gg, pw[pos]));
          } else if(a[i] == 1) {
            // bai
            int tmp;
            if(t) tmp = i - 2;
            else tmp = i - 1;
            Add(dp[i][j + 1][k][t], mul(gg, pw[tmp]));
            if(t) Add(dp[i][j][k + 1][t], mul(gg, pw[tmp]));
          } else {
            // hei
            int pos;
            if(j) pos = i - 2;
            else pos = i - 1;
            Add(dp[i][j][k][t + 1], mul(gg, pw[pos]));
            if(j) Add(dp[i][j][k][t], mul(gg, pw[pos]));
          }
        }
  int ans = 0;
  // for(int o = 0; o <= n; ++o)
  for(int i = 0; i <= n; ++i)
    for(int j = 0; j <= n; ++j)
      for(int k = 0; k <= n; ++k) {
        // if(dp[n][i][j][k]) printf("dp[%d][%d][%d][%d] = %d\n", i, j, k, n - i - j - k, dp[n][i][j][k]);
        int pos = (i + k) % 2;
        if(pos == p) Add(ans, dp[n][i][j][k]);
      }
  printf("%d\n", ans);
  return 0;
}