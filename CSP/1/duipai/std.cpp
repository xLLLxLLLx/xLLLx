#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
ll a[N];

ll cal(ll s, ll d, int id) {
  return s + d * id;
}

int main(){
  int n, m;
  cin >> n >> m;
  for(int o = 1; o <= m; ++o) {
    int l, r;
    ll s, e;
    cin >> l >> r >> s >> e;
    if(r > l) {
      ll d = (e - s) / (r - l);
      for(int i = l; i <= r; ++i)
        a[i] += cal(s, d, i - l);
    } else a[l] += s;
  }
  ll ans = 0;
  for(int i = 1; i <= n; ++i)
    ans ^= a[i];
  printf("%lld\n", ans);
  return 0;
}