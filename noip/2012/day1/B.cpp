#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010, Mask = (1 << 21);
struct data {
  int x, y;
} a[N];
int n;

namespace task1 {
  ll f[Mask];

  void Min(ll &x, ll y) {
    x = min(x, y);
  }

  void solve() {
    int tot = (1 << n) - 1;
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    for(int i = 0; i <= tot; ++i) {
      ll now = a[0].x;
      for(int j = 0; j < n; ++j) {
        if((i >> j) & 1) now *= a[j + 1].x;
      }
      for(int j = 0; j < n; ++j) {
        if((i >> j) & 1) continue;
        Min(f[i | (1 << j)], max(f[i], now / a[j + 1].y));
      }
    }
    printf("%lld\n", f[tot]);
  }
}

int main() {
  scanf("%d", &n);
  for(int i = 0; i <= n; ++i) {
    scanf("%d%d", &a[i].x, &a[i].y);
  }
  if(n <= 20) task1::solve();
  return 0;
}