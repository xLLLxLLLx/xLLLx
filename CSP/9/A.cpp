#include <bits/stdc++.h>
using namespace std;
const int N = 110;
double a[N];

int main() {
  double mx = 0.0;
  int n;
  cin >> n;
  if(n <= 20) {
    for(int i = 0; i < n; ++i)
      cin >> a[i];
    double ans = 0.0;
    for(int i = 1; i < (1 << n); ++i) {
      double base = 1.0;
      for(int j = 0; j < n; ++j) {
        if((i >> j) & 1) base *= (1.0 - a[j]);
      }
      // printf("%lf\n", base);
      double pos = 0.0;
      for(int j = 0; j < n; ++j) {
        if((i >> j) & 1) pos += a[j] * (base / (1.0 - a[j]));
      }
      ans = max(ans, pos);
    }
    printf("%.12f\n", ans);
  } else {
    double ans = 0.0;
    for(int i = 1; i <= n; ++i) {
      cin >> a[i];
    }
    sort(a + 1, a + 1 + n);
    ans = a[n];
    double base = a[n] / (1.0 - a[n]), tmp = 1.0 - a[n];
    for(int i = n - 1; i >= 1; --i) {
      double pos = a[i] / (1.0 - a[i]);
      //if(pos + base <= 1.0) {
        // puts("");
        base += pos;
        tmp *= (1.0 - a[i]);
      //}
      ans = max(ans, base * tmp);
    }
    printf("%.12f\n", ans);
  }
  return 0;
}