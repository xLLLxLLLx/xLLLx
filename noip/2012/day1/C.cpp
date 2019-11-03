//70pts!!
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int n, nt[N][2];
ll a[N], bz;


typedef pair<ll, ll> P;
#define fi first
#define se second

namespace task1 {
  int p[N];

  ll Abs(ll x) {
    if(x < 0) return -x;
    else return x;
  }

  bool cmp(int x, int y) {
    ll pos = Abs(a[x] - bz), tmp = Abs(a[y] - bz);
    return pos == tmp ? a[x] < a[y] : pos < tmp;
  }

  P go(int be, ll lmt) {
    int now = 1;
    ll pos = 0, tmp = 0;
    for(int i = be; i < n; ) {
      // printf("now = %d i = %d\n", now, i);
      if(now) {
        if(!nt[i][1]) break;
        ll gg = Abs(a[i] - a[nt[i][1]]);
        if(pos + tmp + gg > lmt) break;
        tmp += gg;
        i = nt[i][1];
      } else {
        if(!nt[i][0]) break;
        ll gg = Abs(a[i] - a[nt[i][0]]);
        if(pos + tmp + gg > lmt) break;
        pos += gg;
        i = nt[i][0];
      }
      now ^= 1;
    }
    return P(tmp, pos);
  }

  bool check(P x, P y) {
    if(!y.se) return true;
    if(!x.se) return false;
    if(1ll * x.fi * y.se < 1ll * y.fi * x.se) return true;
    else return false;
  }

  void solve() {
    for(int i = 1; i <= n; ++i) {
      p[i] = i;
    }
    for(int i = 1; i < n; ++i) {
      bz = a[i];
      for(int j = i + 1; j <= n; ++j) p[j] = j;
      sort(p + i + 1, p + 1 + n, cmp);
      nt[i][0] = p[i + 1];
      if(i + 2 <= n) nt[i][1] = p[i + 2];
      // printf("i = %d fi = %d se = %d\n", i, nt[i][0], nt[i][1]);
    }
    ll cd;
    scanf("%lld", &cd);
    P tmp = P(0, 0);
    int be = 0;
    // go(1, cd);
    for(int i = 1; i <= n; ++i) {
      P pos = go(i, cd);
      // printf("be = %d A = %lld B = %lld\n", i, pos.fi, pos.se);
      if(check(pos, tmp)) {
        tmp = pos;
        be = i;
      }
    }
    printf("%d\n", be);
    int m;
    scanf("%d", &m);
    for(int o = 1, y; o <= m; ++o) {
      ll x;
      scanf("%d%lld", &y, &x);
      P pos = go(y, x);
      printf("%lld %lld\n", pos.fi, pos.se);
    }
  }
}

namespace task2 {
  int nt[N][2];

  void init() {
    
  }

  void solve() {
    init();
  }
}

int main() {
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
  }
  if(n <= 1000) task1::solve();
  else {
    task2::solve();
  }
  return 0;
}