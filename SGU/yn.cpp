#include <cstdio>
#include <cstring>
#include <algorithm>

typedef long long LL;
const int N = 1200005, MOD = 998244353;

int tc, n;
int fac[N], ifac[N], p[N >> 1], vis[N >> 1];

inline void Read(int &x) {
  x = 0; static char c;
  for (c = getchar(); c < '0' || c > '9'; c = getchar());
  for (; c >= '0' && c <= '9'; x = (x << 3) + (x << 1) + c - '0', c = getchar());
}

inline int Pow(int x, int b) {
  static int re;
  for (re = 1; b; b >>= 1, x = (LL) x * x % MOD)
    if (b & 1) re = (LL) re * x % MOD;
  return re;
}

inline int C(int x, int y) {
  if (x < y) return 0;
  return (LL) fac[x] * ifac[y] % MOD * ifac[x - y] % MOD;
}
inline int Cal(int x, int y) {
  if (x < y) return 0;
  int dis = 2 * x - y, re1 = C(dis, x);
  if (y + 2 > dis) return re1;
  return (re1 - C(dis, (dis + y) / 2 + 1)) % MOD;
}

int main() {
  freopen("inverse.in", "r", stdin);
  freopen("inverse.out", "w", stdout);
  
  fac[0] = 1;
  for (int i = 1; i < N; ++i) {
    fac[i] = (LL) fac[i - 1] * i % MOD;
  }
  ifac[N - 1] = Pow(fac[N - 1], MOD - 2);
  for (int i = N - 1; i >= 1; --i) {
    ifac[i - 1] = (LL) ifac[i] * i % MOD;
  }
  
  scanf("%d", &tc);
  for (; tc; --tc) {
    int re = 0, mx = 0, low = 1, he = 0;
    memset(vis, 0, sizeof vis);
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i) {
      Read(p[i]);
    }
    for (int i = 1; i < n; ++i, --he) {
      if (mx < p[i]) he += p[i] - mx;
      mx = std::max(mx, p[i]);
      for (vis[p[i]] = 1; vis[low]; ++low);
      re = (re + Cal(n - i + 1, he + 1)) % MOD;
      if (mx > p[i] && p[i] > low) {
        break;
      }
      printf("%lld\n", re);
    }
    printf("%d\n", (re + MOD) % MOD);
  }

  return 0;
}