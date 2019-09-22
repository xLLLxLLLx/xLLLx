#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 210;
ll f[N][2];

int main() {
  // int n;
  // scanf("%d", &n);
  for(int n = 100; n <= 200; ++n) {
    memset(f, 0, sizeof f);
  f[0][0] = 1;
  for(int i = 0; i < n; ++i) {
    for(int j = 50; j <= n - i; ++j) {
      f[i + j][1] += f[i][0];
    }
    f[i + 1][0] += f[i][0] + f[i][1];
  }
  // printf("%lld\n", f[n][0] + f[n][1]);
  if(f[n][0] + f[n][1] >= 1000000) {
    return printf("%d\n", n), 0;
  }
  }
  return 0;
}