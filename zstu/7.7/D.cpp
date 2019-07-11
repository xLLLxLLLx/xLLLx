#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
const int mod = 1e9 + 7;
ll jc[N]={1}, f[N];

void Add(ll &x, ll y) {
	x = (x + y) % mod;
}

void Mul(ll &x, ll y) {
	x = (x * y) % mod;
}

ll add(ll x, ll y) {
	return (x + y) % mod;
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

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) jc[i] = mul(jc[i - 1], i);
	ll ans = jc[n];
	Mul(ans, q_pow(jc[n / 2], mod - 2));
	f[2] = 1, f[3] = 2;
	for(int i = 4; i <= n / 2; ++i) {
		f[i] = mul(i - 1, add(f[i - 1], f[i - 2]));
	}
	Mul(ans, f[n / 2]);
	printf("%lld\n", ans);
	return 0;
}