#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e4 + 10;
struct data {
  int m, s, p;
} a[N];
ll v[N];
int r, b, c;

bool cmp(ll x, ll y) {
  return x > y;
}

bool check(ll x) {
  for(int i = 1; i <= c; ++i) {
    v[i] = min((x - a[i].p) / a[i].s, 1ll * a[i].m);
  }
  sort(v + 1, v + 1 + c, cmp);
  ll ans = 0;
  for(int i = 1; i <= r; ++i) {
    ans += v[i];
    if(ans >= b) return true;
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    cin >> r >> b >> c;
    for(int i = 1; i <= c; ++i) {
      scanf("%d%d%d", &a[i].m, &a[i].s, &a[i].p);
    }
    ll l = 1, r = 2e18, ans = 0;
    while(l <= r) {
      ll mid = (l + r) >> 1;
      if(check(mid)) 
        ans = mid, r = mid - 1;
      else 
        l = mid + 1;
    }
    printf("Case #%d: %lld\n", o, ans);
  }
  return 0;
}