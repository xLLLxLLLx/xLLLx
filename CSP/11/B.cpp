#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
double f[N][2][2], v[N][2][2];
int n, p, L[N], R[N];

int get(int l, int r) {
  int pos = l - (l % p);
  return (r - pos) / p + (l % p == 0);
}

int main() {
  scanf("%d%d", &n, &p);
  for(int i = 1; i <= n; ++i) {
    scanf("%d%d", &L[i], &R[i]);
    // cout << get(L[i], R[i]) << endl;
  }
  {
    double tt = get(L[1], R[1]), len = (R[1] - L[1] + 1);
    double P = tt / len, Q = 1.0 - P;
    // cout << P << " " << Q << endl;
    // v[1][1][1] = 2000.0;
    f[1][1][1] = P;
    v[1][1][1] = P * 2000.0;
    f[1][0][0] = 0.0;
  }
  for(int i = 2; i <= n; ++i) 
    for(int j = 0; j < 2; ++j) 
      for(int k = 0; k < 2; ++k) {
        // printf("f[%d][%d][%d] = %lf\n", i - 1, j, k, f[i - 1][j][k]);
        double pos = f[i - 1][j][k], tmp = v[i - 1][j][k];
        double tt = get(L[i], R[i]), len = R[i] - L[i] + 1;
        double P = tt / len, Q = 1.0 - P;
        // cout << P << " " << Q << endl;
        v[i][j][0] += (tmp + k * 2000.0 * pos) * Q;
        f[i][j][0] += pos * Q;
        f[i][j][1] += pos * P;
        if(i == n) v[i][j][1] += (tmp + (2 - k - j) * 2000.0 * pos) * P;
        else v[i][j][1] += (tmp + 2000.0 * pos) * P;
        // if(i == n) v[i][j][1] += tmp + (2 - k - j) * 2000.0;
        // else v[i][j][1] += tmp + 2000.0;
  }
  double ans = 0.0;
  for(int i = 0; i < 2; ++i)
    for(int j = 0; j < 2; ++j) {
      ans += v[n][i][j];//* v[n][i][j];
      // printf("f[%d][%d] = %lf, v = %lf\n", i, j, f[n][i][j], v[n][i][j]);
    }
  printf("%.10f\n", ans);
  return 0;
}