#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
ll c[N];

void add(int l, int r, ll w) {
  c[l] += w;
  c[r + 1] -= w;
}

int main() {
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= m; ++i) {
    int l, r;
    ll s, e;
    cin >> l >> r >> s >> e;
    if(r > l) {
      ll d = (e - s) / (r - l);
      add(l, l, s);
      add(l + 1, r, d);
      add(r + 1, n, -e);
    } else {
      add(l, l, s);
      add(l + 1, n, -s);
    }
  }
  for(int i = 1; i <= n; ++i) c[i] += c[i - 1];
  for(int i = 1; i <= n; ++i) c[i] += c[i - 1];
  ll ans = 0;
  for(int i = 1; i <= n; ++i)
    ans ^= c[i];
  printf("%lld\n", ans);
  return 0;
}