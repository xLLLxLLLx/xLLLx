#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
int a[N], qz[N];

bool cmp(int x, int y) {
  return a[x] > a[y];
}

int main() {
  int n, k;
  scanf("%d%d", &n, &k);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  ll ans = 0;
  for(int i = 1; i <= n; ++i) {
    qz[i] = (qz[i - 1] + a[i]) % k;
  }
  for(int i = 1; i <= n; ++i) {
    int maxn = a[i];
    for(int j = i + 1; j <= n; ++j) {
      maxn = max(maxn, a[j]);
      int pos = ((qz[j] - qz[i - 1] - maxn) % k + k) % k;
      if(!pos) ans++;
    }
  }
  printf("%lld\n", ans);
  return 0;
}