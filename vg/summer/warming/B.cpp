#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll n, k;

ll js(ll x) {
	return x * (1 + x) / 2;
}

bool check(ll x) {
	return js(n - x) - x <= k;
}

int main() {
	cin >> n >> k;
	ll l = 0, r = n, ans = 0;
	while(l <= r) {
		ll mid = (l + r) >> 1;
		if(check(mid)) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	printf("%lld\n", ans);
	return 0;
}