#include <bits/stdc++.h>
using namespace std;
double r1, r2;

double f(double x) {
  return sqrt((r1 * r1 - x * x) * (r2 * r2 - x * x));
}

double simp(double l, double r) {
  double mid = (l + r) / 2.0;
  return (f(l) + 4.0 * f(mid) + f(r)) * (r - l) / 6.0;
}

double go(double l, double r, double eps) {
  double mid = (l + r) / 2.0;
  double st = simp(l, r), sl = simp(l, mid), sr = simp(mid, r);
  if(fabs(sl + sr - st) <= 15.0 * eps) return sl + sr + (sl + sr - st) / 15.0;
  return go(l, mid, eps / 2.0) + go(mid, r, eps / 2.0);
}

int main() {
  freopen("twocyl.in", "r", stdin);
  freopen("twocyl.out", "w", stdout);
  cin >> r1 >> r2;
  printf("%.8f\n", go(0, min(r1, r2), 1e-4) * 8);
  return 0;
}