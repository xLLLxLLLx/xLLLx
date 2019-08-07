#include <bits/stdc++.h>
#define ll __int128
using namespace std;

ll gcd(ll x, ll y) {
	return y ? gcd(y, x % y) : x;
}

ll solve(ll l, ll m, ll k) {
	ll d = gcd(m, k);
	if(d == 1)
		return l;
	if(l > k / d)
		return m * (k - l) / d + solve((k - m * (k - l)) / d, m, k / d);
	return l;
}

ll m, k;

signed main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%lld%lld", &m, &k);
		printf("%lld\n", solve(k - 1, m, k) + 1);
	}
	return 0;
}