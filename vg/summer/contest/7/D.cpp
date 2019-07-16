#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, mod = 1e9 + 7;
ll jc[N] = {1}, ny[N] = {1};

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) {
			ans = ans * x % mod;
		}
		x = x * x % mod;
	}
	return ans;
}

ll C(int x, int y) {
	if(y > x) return 0ll;
	return jc[x] * ny[y] % mod * ny[x - y] % mod;
}

ll A(int x, int y) {
	return jc[x] * ny[x - y] % mod;
}

int main() {
	int n, m, a, b;
	cin >> n >> m >> a >> b;
	ll ans = 0;
	for(int i = 1; i < N; ++i) jc[i] = jc[i - 1] * i % mod, ny[i] = q_pow(jc[i], mod - 2);
	for(int i = 1; i <= n - 1; ++i) {
		ll pos = A(n - 2, i - 1) * q_pow(m, n - 1 - i) % mod * C(m - 1, i - 1) % mod;
		if(i != n - 1) pos = pos * (i + 1) % mod * q_pow(n, n - i - 2) % mod;
		ans = (ans + pos) % mod;
	}
	printf("%lld\n", ans);
	return 0;
}