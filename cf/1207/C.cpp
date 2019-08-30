#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
ll f[N][2];
int a[N], b[N];

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int n, pos = 0, be = -1, ed;
    ll x, y;
    scanf("%d%lld%lld", &n, &x, &y);
    for(int i = 1; i <= n; ++i) {
      scanf("%1d", &a[i]);
      if(i > 1)
        b[i - 1] = max(a[i], a[i - 1]);
    }
    b[0] = b[n] = 0;
    int sum = 0;
    for(int i = 0; i <= n; ++i)
      sum += b[i] + 1;
    ll tot = 1ll * x * n + 1ll * y * sum;
    // printf("tot%lld\n", tot);
    for(int i = 0; i <= n; ++i) f[i][0] = f[i][1] = 1e18;
    f[0][0] = 0;
    for(int i = 1; i <= n; ++i) {
      if(b[i]) {
        f[i][1] = min(f[i][1], f[i - 1][0] + x);
        f[i][1] = min(f[i][1], f[i - 1][1]);
      } else {
        f[i][0] = min(f[i][0], f[i - 1][0]);
        f[i][0] = min(f[i][0], f[i - 1][1] + x);
        f[i][1] = min(f[i][1], f[i - 1][1] + y);
        f[i][1] = min(f[i][1], f[i - 1][0] + x + y);
      }
      // printf("f[%d][%d]=%lld, f[%d][%d]=%lld\n", i, 0, f[i][0], i, 1,f[i][1]);
    }
    printf("%lld\n", f[n][0] + tot);
  }
  return 0;
}