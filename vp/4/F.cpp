#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, LOG = 20;
int a[N], qz[N], st[N][LOG + 1];

int get(int l, int r) {
  int k = (int)(log(double(r - l + 1)) / log(2.0));
  return min(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
  freopen("positive.in", "r", stdin);
  freopen("positive.out", "w", stdout);
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    qz[i] = qz[i - 1] + a[i];
    st[i][0] = qz[i];
  }
  for(int j = 1; j <= LOG; ++j)
    for(int i = 0; i <= n; ++i) {
      if(i + (1 << j) > n + 1) break;
      st[i][j] = min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
    }
  int ans = 0;
  for(int i = 1; i <= n; ++i) {
    int pos = get(0, i - 1), tmp = get(i, n);
    if(pos + qz[n] - qz[i - 1] > 0 && tmp - qz[i - 1] > 0) {
      // printf("%d %d %d\n", pos, tmp, i);
      ans++;
    }
  }
  printf("%d\n", ans);
  return 0;
}