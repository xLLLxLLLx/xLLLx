#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3010, mod = 998244353;
ll jc[N] = {1}, ny[N] = {1}, f[N], d[N];

void Add(ll &x, ll y) {
	x = (x + y + mod) % mod;
}

void Mul(ll &x, ll y) {
	x = (x * y) % mod;
}

ll add(ll x, ll y) {
	return (x + y + mod) % mod;
}

ll mul(ll x, ll y) {
	return x * y % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

ll C(int x, int y) {
	return mul(jc[x], mul(ny[y], ny[x - y]));
}

int main() {
	int n;
	for(int i = 1; i < N; ++i) 
		jc[i] = mul(jc[i - 1], i), ny[i] = q_pow(jc[i], mod - 2);
	f[0] = 0, f[1] = 0;
	for(int i = 2; i < N; ++i) {
		ll pos = q_pow(add(q_pow(2, i), -1), mod - 2);
		f[i] = mul(i * (i - 1), q_pow(2, i - 2));
		for(int j = 0; j < i; ++j) {
			Add(f[i], mul(C(i, j), f[j]));
		}
		Mul(f[i], pos);
	}
	for(int i = 1; i < N; ++i) {
		ll pos = q_pow(i, mod - 2);
		for(int j = 1; j <= i; ++j)
			Add(d[i], f[j]);
		Mul(d[i], pos);
	}
	while(scanf("%d", &n) == 1) {
		printf("%lld\n", d[n]);
	}
	return 0;
}