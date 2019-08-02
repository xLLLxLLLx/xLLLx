#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7;
int n, k;
map<int, ll> f;

ll add(ll x, ll y) {
	return (x + y + mod) % mod;
}

void Add(ll &x, ll y) {
	x = (x + y + mod) % mod;
}

ll mul(ll x, ll y) {
	return (x * y) % mod;
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

ll get(int x) {
	if(!f.count(x)) {
		int len = sqrt(x);
		ll pos = q_pow(k, (x / 2) + (x & 1));
		for(int i = 2; i <= len; ++i) {
			if(x % i) continue;
			Add(pos, -get(i));
			if(i * i != x) Add(pos, -get(x / i));
		}
		if(x != 1) Add(pos, -k);
		return f[x] = pos;
	} else return f[x];
}

int main() {
	scanf("%d%d", &n, &k);
	int len = sqrt(n);
	ll ans = 0;
	for(int i = 1; i <= len; ++i) {
		if(n % i) continue;
		if(i & 1) Add(ans, mul(i, get(i)));
		else Add(ans, mul(i / 2, get(i)));
		if(i * i != n) {
			int now = n / i;
			if(now & 1) Add(ans, mul(now, get(now)));
			else Add(ans, mul(now / 2, get(now)));
		}
	}
	printf("%lld\n", (ans + mod) % mod);
	return 0;
}