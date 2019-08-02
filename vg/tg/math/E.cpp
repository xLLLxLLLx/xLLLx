#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, mod = 1000003;
ll jc[N] = {1}, ny[N] = {1};

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = ans * x % mod;
		x = x * x % mod;
	}
	return ans;
}

void init() {
	for(int i = 1; i < N; ++i) {
		jc[i] = jc[i - 1] * i % mod;
		ny[i] = q_pow(jc[i], mod - 2);
	}
}

ll C(int x, int y) {
	return jc[x] * ny[y] % mod * ny[x - y] % mod;
}

int main() {
	int T;
	scanf("%d", &T);
	init();
	for(int o = 1, x, y; o <= T; ++o) {
		scanf("%d%d", &x, &y);
		printf("Case %d: %lld\n", o, C(x, y));
	}
	return 0;
}