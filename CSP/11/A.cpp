#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];

void read(int &x) {
  char ch = getchar(); x = 0;
  for(; ch < '0' || ch > '9'; ch = getchar()) ;
  for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

int main() {
  int n, q;
  read(n), read(q);
  ll suma = 0, sumb = 0, pos = 0;
  for(int i = 1; i <= n; ++i) {
    read(a[i]);
    suma += a[i];
  }
  for(int i = 1; i <= n; ++i) {
    read(b[i]);
    sumb += b[i];
    pos += 1ll * a[i] * b[i];
  }
  for(int o = 1, tp, x, y; o <= q; ++o) {
    read(tp), read(x), read(y);
    if(tp == 1) {
      suma -= a[x];
      pos -= 1ll * a[x] * b[x];
      a[x] = y;
      suma += a[x];
      pos += 1ll * a[x] * b[x];
    } else {
      sumb -= b[x];
      pos -= 1ll * a[x] * b[x];
      b[x] = y;
      sumb += b[x];
      pos += 1ll * a[x] * b[x];
    }
    ll ans = 1ll * (n - 1) * pos - (suma * sumb - pos);
    printf("%lld\n", ans);
  }
  return 0;
}