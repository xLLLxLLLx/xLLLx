#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
double b1, t1, b2, t2, l, ds, df, g;

double check(double b, double t, double x, double s) {
  double h = s - s * s / x;
  if(b <= h && h <= t) return g * x;
  if(h > t) h = t;
  if(h < b) h = b;
  double gg = g * s * (x - s) * 0.5 / h;
  return gg + g * g * x * x / (4 * gg);
}

double get(double x) {
  return max(check(b1, t1, x + ds, ds), check(b2, t2, l - x + df, l - x));
}

int main() {
  freopen("jumper.in", "r", stdin);
  freopen("jumper.out", "w", stdout);
  while (~scanf("%lf%lf%lf%lf%lf%lf%lf%lf", &b1, &t1, &b2, &t2, &l, &ds, &df, &g)){
    double L = 0, R = l;
    for(int o = 1; o <= 200; ++o) {
      double rL = L + (R - L) / 3, rR = R - (R - L) / 3;
      get(rL) - get(rR) < -eps ? R = rR : L = rL;
    }
    printf("%.4f\n", sqrt(get(L)));
  }
  return 0;
}