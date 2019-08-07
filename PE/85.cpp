#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll Abs(ll x) {
	if(x < 0) x = -x;
	return x;
}

int main() {
	ll pos = 1e18, A = 0, bi, bj;
	ll maxn = 8000000;
	for(int i = 1; i <= maxn; ++i) {
		ll tmp = 1ll * i * (i + 1);
		ll gg = maxn / tmp;
		if(gg <= 0) break;
		gg++;
		gg = sqrt(gg);
		for(int j = gg - 1000; j <= gg + 1000; ++j) {
			if(j <= 0) continue;
			ll now = 1ll * j * (j + 1) * tmp;
			ll res = Abs(now - maxn);
			if(res < pos) {
				pos = res;
				A = 1ll * i * j;
				bi = i, bj = j;
			}
		}
	}
	printf("%lld\n", A);
	printf("%lld %lld %lld\n", bi, bj, pos);
	return 0;
}