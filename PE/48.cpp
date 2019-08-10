#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1e10;

int main() {
	ll ans = 0;
	for(int i = 1; i <= 1000; ++i) {
		ll pos = 1;
		for(int j = 1; j <= i; ++j) {
			pos = pos * i % mod;
		}
		ans += pos;
		ans %= mod;
	}
	printf("%lld\n", ans);
	return 0;
}