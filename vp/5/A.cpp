#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int mod, n, m;
int a[N][N];

int add(int x, int y) {
  return (x + y) % mod;
}

int mul(int x, int y) {
  return x * y % mod;
}

int q_pow(int x, int y) {
  int ans = 1;
  for(; y; y >>= 1) {
    if(y & 1) ans = mul(x, ans);
    x = mul(x, x);
  }
  return ans;
}

void init() {
  for(int i = 1; i < N; ++i) a[1][i] = 2 * i;
}

int main() {
  freopen("ackerman.in", "r", stdin);
  freopen("ackerman.out", "w", stdout);
  scanf("%d", &mod);
  init();
  while(scanf("%d%d", &n, &m) == 2 && (n || m) ) {
    printf("%d\n", a[n][m]);
  }
  return 0;
}