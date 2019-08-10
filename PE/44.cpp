#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<ll, int> mp;

int main() {
	ll maxn = 1e18;
	int n = 1e4;
	for(int i = 1; i <= n; ++i) {
		ll pos = 1ll * i * (3ll * i - 1) / 2;
		mp[pos] = 1;
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j < i; ++j) {
			ll pos = 1ll * i * (3ll * i - 1) / 2;
			ll tmp = 1ll * j * (3ll * j - 1) / 2;
			if(mp[pos - tmp] && mp[pos + tmp]) {
				maxn = min(maxn, pos - tmp);
			}
		}
	printf("%lld\n", maxn);
	return 0;
}