#include <bits/stdc++.h>
using namespace std;
const int N = 110, M = 50000 + 10;
struct data {
  int x, y;
} a[N];
double f[M];

double pf(double x) {
  return x * x;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int n, p, flg = 1, tot = 0, qwq = 0;
    scanf("%d%d", &n, &p);
    for(int i = 1; i <= n; ++i) {
      scanf("%d%d", &a[i].x, &a[i].y);
      if(a[i].x > a[i].y) swap(a[i].x, a[i].y);
      qwq += 2 * a[i].x;
      tot += 2 * (a[i].x + a[i].y);
    }
    double maxn = tot;
    memset(f, 0, sizeof f);
    int remain = min(p - tot, qwq);
    for(int i = 1; i <= n; ++i)
      for(int j = remain; j >= a[i].x * 2; --j) {
        f[j] = max(f[j - a[i].x * 2] + 2.0 * sqrt(pf(a[i].x) + pf(a[i].y)), f[j]);
      }
    double pos = 0;
    for(int i = 0; i <= remain; ++i)
      pos = max(pos, f[i]);
    printf("Case #%d: %.12f\n", o, min(double(p), maxn + pos));
  }
  return 0;
}