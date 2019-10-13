#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
ll a[N];

void add(int l, int r, ll w) {
  a[l] += w;
  a[r + 1] -= w;
}

int main() {
  int n, q;
  scanf("%d%d", &n, &q);  
  for(int o = 1, l, r; o <= q; ++o) {
    ll s, e;
    scanf("%d%d%lld%lld", &l, &r, &s, &e);
    add(l, l, s);
    if(l < r) {
      ll d = (e - s) / (r - l);
      add(l + 1, r, d);
      add(r + 1, n, - s - d);
    } else add(r + 1, n, -s);
  }
  for(int i = 1; i <= n; ++i) a[i] += a[i - 1];
  for(int i = 1; i <= n; ++i) a[i] += a[i - 1];
  ll ans = 0;
  for(int i = 1; i <= n; ++i) {
    // printf("%lld\n", a[i]);
    ans ^= a[i];
  }
  printf("%lld\n", ans);
  return 0;
}
