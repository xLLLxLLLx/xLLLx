#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e6 + 11, mod = 998244353;
int rev[N], nm[N];
ll jc[N] = {1}, ny[N] = {1};
ll a[N], b[N], g[N];

ll q_pow(ll x, int y) {
  ll ans = 1;
  for(; y; y >>= 1) {
    if(y & 1) ans = ans * x % mod;
    x = x * x % mod;
  }
  return ans;
}

void ntt(ll a[], int len) {
  for(int i = 0; i < len; ++i) {
    if(rev[i] > i) 
      swap(a[i], a[rev[i]]);
  }
  for(int t = len >> 1, d = 1; d < len; t >>= 1, d <<= 1)
    for(int i = 0; i < len; i += (d << 1))
      for(int j = 0; j < d; ++j) {
        ll tmp = g[t * j] * a[i + j + d] % mod;
        a[i + j + d] = (a[i + j] - tmp + mod) % mod;
        a[i + j] = (a[i + j] + tmp) % mod;
      }
}

void goNTT(ll a[], ll b[], int len, int L) {
  for(int i = 0; i < len; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
  }
  g[0] = 1, g[1] = q_pow(3, (mod - 1) / len);
  for(int i = 2; i < len; ++i) {
    g[i] = g[i - 1] * g[1] % mod;
  }
  ntt(a, len), ntt(b, len);
  for(int i = 0; i < len; ++i) {
    a[i] = a[i] * b[i] % mod;
  }
  g[1] = q_pow(g[1], mod - 2);
  for(int i = 2; i < len; ++i) {
    g[i] = g[i - 1] * g[1] % mod;
  }
  ntt(a, len);
  ll pos = q_pow(len, mod - 2);
  for(int i = 0; i < len; ++i) {
    a[i] = a[i] * pos % mod;
    b[i] = 0;
  }
}

ll C(int x, int y) {
	return jc[x] * ny[y] % mod * ny[x - y] % mod;
}

int MAXN = 2e6;

void init() {
  for(int i = 1; i <= MAXN; ++i) {
    jc[i] = jc[i - 1] * i % mod;
  }
  ny[MAXN] = q_pow(jc[MAXN], mod - 2);
  for(int i = MAXN - 1; i >= 0; --i)
    ny[i] = ny[i + 1] * (i + 1) % mod;
}

int main() {
	int T;
	init();
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m;
		int len = 1, L = 0;
		scanf("%d%d", &n, &m);
		nm[1] = nm[2] = nm[3] = 0;
		for(int i = 0; i < n; ++i) {
			scanf("%lld", &a[i]);
		}
		for(int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			nm[x]++;
		}
		for(; len < 2 * n; len <<= 1, L++) ;
		for(int c = 3; c >= 1; --c) {
			if(!nm[c]) continue;
			for(int i = 0; i * c < n; ++i) 
				b[i * c] = C(nm[c] - 1 + i, i);
      for(int i = 0; i < n; ++i) {
        printf("%lld ", a[i]);
      }
      puts("");
			goNTT(a, b, len, L);
		}
    for(int i = 0; i < n; ++i) {
      printf("%lld ", a[i]);
    }
    puts("");
		ll ans = 0;
		for(int i = 0; i < n; ++i) {
      a[i] %= mod;
      // printf("%lld ", a[i]);
			ans ^= 1ll * (i + 1) * a[i];
		}
		// printf("%lld\n", ans);
	}
	return 0;
}