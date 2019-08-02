#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
ll a[N];

int main() {
	int n, x;
	cin >> n >> x;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	ll pos = 0;
	for(int i = 2; i <= n; ++i) {
		ll gg = max(0ll, (a[i] + a[i - 1]) - x);
		a[i] -= min(a[i], gg);
		pos += gg;
	}
	printf("%lld\n", pos);
	return 0;
}