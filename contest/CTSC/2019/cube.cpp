#pragma GCC optimize(2)
#pragma GCC optimize(3,"Ofast","inline")
#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e6 + 1, mod = 998244353;
ll jc[N], ny[N], f[N], g[N], inv[N];

ll mul(ll x, ll y) {
	return x * y % mod;
}

ll add(ll x, ll y) {
	x += y;
	while(x >= mod) x -= mod;
	while(x < 0) x += mod;
	return x;
}

ll sub(ll x, ll y) {
	x -= y;
	while(x >= mod) x -= mod;
	while(x < 0) x += mod;
	return x;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

ll C(int x, int y) {
	if(x < y) return 0;
	return mul(jc[x], mul(ny[y], ny[x - y]));
}

void init() {
	jc[0] = ny[0] = 1;
	for(int i = 1; i < N; ++i)
		jc[i] = mul(jc[i - 1], i);
	ny[N - 1] = q_pow(jc[N - 1], mod - 2);
	for(int i = N - 2; i >= 1; --i)
		ny[i] = mul(ny[i + 1], i + 1);
}

int n, m, l, k;
ll tot;

ll js(int x) {
	return mul(n - x, mul(m - x, l - x));
}

int main() {
	init();
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d%d%d%d", &n, &m, &l, &k);
		int mi = min(n, min(m, l));
		ll ans = 0, opt = -1, res = 1, tmp = 1;
		if(k & 1) opt = 1;
		f[0] = js(0), g[0] = 1;
		for(int i = 1; i <= mi; ++i) {
			f[i] = js(i);
			g[i] = sub(f[0], f[i]);
			tmp = mul(tmp, g[i]);
		}
		inv[mi] = q_pow(tmp, mod - 2);
		for(int i = mi - 1; i >= 1; --i)
			inv[i] = mul(inv[i + 1], g[i + 1]);
		for(int i = 1; i <= mi; ++i)
			f[i] = mul(f[i - 1], f[i]);
		for(int i = k; i <= mi; ++i) {
			if(abs(i - k) & 1)
				ans = add(ans, sub(mod, mul(C(i, k), mul(f[i - 1], inv[i]))));
			else 
				ans = add(ans, mul(C(i, k), mul(f[i - 1], inv[i])));
		}
		printf("%lld\n", (ans + mod) % mod);
	}
	return 0;
}