#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = (1 << 20) + 1, M = 55, K = 21;
char lx[M][K];
int cnt[N];
double dp[N];
ll f[N];

void init() {
  for(int i = 0; i < N; ++i)
    cnt[i] = cnt[i >> 1] + (i & 1);
}

int main() {
  init();
  int n;
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    scanf("%s", lx[i]);
  }
  int pos = strlen(lx[0]), tot = (1 << pos);
  for(int i = 0; i < n; ++i)
    for(int j = i + 1; j < n; ++j) {
      int mk = 0;
      for(int k = 0; k < pos; ++k) {
        if(lx[i][k] == lx[j][k]) mk |= (1 << k);
      }
      f[mk] |= (1ll << i) + (1ll << j);
    }
  // f[0] = 0;
  for(int i = tot - 1; i >= 0; --i) { 
    // printf("now = %d\n", i);
    for(int j = 0; j < pos; ++j) {
      if((i >> j) & 1) {
        f[i ^ (1 << j)] |= f[i];
      }
    }
    // printf("f[%d] = %lld\n", i, f[i]);
  }
  double ans = 0;
  dp[0] = 1;
  for(int i = 0; i < tot; ++i) {
    for(int j = 0; j < pos; ++j) {
      if((i >> j) & 1) continue;
      dp[i | (1 << j)] += dp[i] / double(pos - cnt[i]);
    }
    int res = 0;
    for(int j = 0; j < n; ++j)
      if(f[i] & (1ll << j)) res++;
    // printf("%d %d\n", i, res);
    ans += dp[i] * (double)res / (double)n;
    // printf("%d\n", res);
  }
  printf("%.12f\n", ans);
  return 0;
}