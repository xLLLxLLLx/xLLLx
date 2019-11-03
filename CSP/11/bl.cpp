#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int n, a[N], b[N];

ll cal() {
  ll ans = 0;
  for(int j = 1; j <= n; ++j)
    for(int k = j + 1; k <= n; ++k) {
      ans += 1ll * (a[k] - a[j]) * (b[k] - b[j]);
    }
  return ans;
}

int main() {
  int q;
  scanf("%d%d", &n, &q);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &b[i]);
  }
  for(int o = 1, tp, x, y; o <= q; ++o) {
    scanf("%d%d%d", &tp, &x, &y);
    if(tp == 1) {
      a[x] = y;
    } else {
      b[x] = y;
    }
    printf("%lld\n", cal());
  }
  return 0;
}