#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], g[N];

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int sum, n, ans = 0;
    scanf("%d%d", &sum, &n);
    int base = sum;
    g[base] = 0;
    for(int i = base - 1; i >= 0; --i) {
      int pos = ((int)(i * 1000.0 / base)) % 10;
      if(pos >= 5) {
        g[i] = 0;
      } else {
        g[i] = g[i + 1] + 1;
      }
    }
    for(int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      sum -= a[i];
      ans += a[i] * 100 / base;
      a[i] = g[a[i]];
    }
    sort(a + 1, a + 1 + n);
    for(int i = 1; i <= n; ++i) {
      if(sum >= a[i]) {
        sum -= a[i];
        ans += (a[i] * 100 / base + 1);
      }
    }
    /*for(int i = 0; i <= n; ++i)
      printf("g[%d] = %d\n", i, g[i]);*/
    ans += (sum / g[0]) * (g[0] * 100 / base + 1);
    sum %= g[0];
    ans += sum * 100 / base;
    printf("Case #%d: %d\n", o, ans);
  }
  return 0;
}