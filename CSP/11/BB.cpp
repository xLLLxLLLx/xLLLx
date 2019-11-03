#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
double f[N][2][2], v[N][2][2];
int n, p, L[N], R[N];

int get(int l, int r) {
  return r / p - (l - 1) / p;
}

int main() {
  scanf("%d%d", &n, &p);
  for(int i = 0; i < n; ++i) {
    scanf("%d%d", &L[i], &R[i]);
    // cout << get(L[i], R[i]) << endl;
  }
  double ans = 0.0;
  for(int i = 0; i < n; ++i) {
    double tt = get(L[i], R[i]), TT = (R[i] - L[i] + 1);
    double uu = get(L[(i + 1) % n], R[(i + 1) % n]), UU = (R[(i + 1) % n] - L[(i + 1) % n] + 1);
    double p = (double)tt / TT, q = (double)uu / UU;
    ans += (p * q + (1.0 - p) * q + (1.0 - q) * p) * 2000.0;
  }
  printf("%.10f\n", ans);
  return 0;
}