#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	ll k, d, t;
	cin >> k >> d >> t;
	ll pos = k / d, yu = k % d;
	if(!yu) {
		return printf("%lld\n", t), 0;
	}
	t *= 2ll;
	ll tmp = (pos * d + yu) * 2 + (d - yu);
	ll gg = t / tmp * (pos + 1) * d, sx = t % tmp;
	double ans = gg;
	if(sx <= (pos * d + yu) * 2) {
		ans += double(sx) / 2.0;
	} else {
		ans += sx - (d * pos + yu);
	}
	printf("%.12f\n", ans);
	return 0;
}