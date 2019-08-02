#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2010, mod = 998244353;
ll f[N], strong[N], cp[N][N];

ll add(ll x, ll y) {
	return (x + y + mod) % mod;
}

ll mul(ll x, ll y) {
	return x * y % mod;
}

void Add(ll &x, ll y) {
	x = (x + y + mod) % mod;
}

void Mul(ll &x, ll y) {
	x = (x * y) % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

ll rev(ll x) {
	return q_pow(x, mod - 2);
}

int main() {
	int n, a, b;
	scanf("%d%d%d", &n, &a, &b);
	ll p = mul(a, rev(b));
	cp[0][0] = 1;
	for(int i = 1; i <= n; ++i) {
		cp[i][0] = 1;
		for(int j = 1; j <= i; ++j) {
			cp[i][j] = add(mul(cp[i - 1][j], q_pow(1 - p + mod, j)), mul(cp[i - 1][j - 1], q_pow(p, i - j)));
		}
	}
	// for(int i = 1; i <= n; ++i)
	// 	for(int j = 1; j <= i; ++j) {
	// 		printf("%d %d %lld\n", i, j, cp[i][j]);
	// 	}
	for(int i = 1; i <= n; ++i) {
		strong[i] = 1;
		for(int j = 1; j < i; ++j) {
			Add(strong[i], -mul(strong[j], cp[i][j]));
		}
	}
	// for(int i = 1; i <= n; ++i) {
	// 	printf("%d %lld\n", i, strong[i]);
	// }
	f[0] = f[1] = 0;
	for(int i = 2; i <= n; ++i) {
		ll pos = 0, tmp = 1;
		for(int j = 1; j <= i; ++j) {
			ll xs = mul(strong[j], cp[i][j]);
			Add(pos, mul(xs, add(mul(j, i - j), mul(j * (j - 1), rev(2)))));
			Add(pos, mul(xs, f[i - j]));
			if(j == i) Add(tmp, -xs);
				else Add(pos, mul(xs, f[j]));
		}
		f[i] = mul(pos, rev(tmp));
		// printf("%d %lld\n", i, f[i]);
	}
	printf("%lld\n", f[n]);
	return 0;
}