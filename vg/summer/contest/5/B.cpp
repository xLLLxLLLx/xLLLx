#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n;

ll get(ll x, ll len, int gg) {
	if((x & 1) == gg) return x / 2 + gg;
	else {
		ll pos = x / 2 + (gg ^ 1);
		return get(pos, (len + (gg ^ 1))/ 2, gg ^ (len & 1)) + (len + gg) / 2;
	}
}

int main() {
	int q;
	scanf("%lld%d", &n, &q);
	for(int o = 1; o <= q; ++o) {
		ll x;
		scanf("%lld", &x);
		printf("%lld\n", get(x, n, 1));
	}
	return 0;
}