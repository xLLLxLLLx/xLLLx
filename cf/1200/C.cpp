#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll gcd(ll x, ll y) {
	return y ? gcd(y, x % y) : x;
}

int main() {
	ll n, m;
	int q;
	cin >> n >> m >> q;
	ll gg = gcd(n, m);
	ll pos = n / gg, tmp = m / gg;
	for(int o = 1; o <= q; ++o) {
		ll x, y, nx, ny;
		scanf("%lld%lld%lld%lld", &x, &y, &nx, &ny);
		ll res, yu;
		if(x == 1) {
			res = y / pos;
			if(y % pos) res++;
		} else {
			res = y / tmp;
			if(y % tmp) res++;
		}
		if(nx == 1) {
			yu = ny / pos;
			if(ny % pos) yu++;
		} else {
			yu = ny / tmp;
			if(ny % tmp) yu++;
		}
		if(yu == res) {
			puts("YES");
		} else {
			puts("NO");
		}
	}
	return 0;
}