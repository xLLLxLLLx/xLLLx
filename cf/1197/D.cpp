#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
ll a[N], dp[N];

int main() {
	int n, m, k;
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	memset(dp, 0, sizeof dp);
	for(int i = n; i >= 1; --i) {
		// printf("now=%d\n", i);
		ll pos = -k;
		for(int j = 1; j <= m; ++j) {
			if(i + j - 1 > n) break;
			// printf("%lld %lld\n", pos, dp[i]);
			pos += a[i + j - 1];
			dp[i] = max(dp[i], pos + dp[i + j]);
		}
	}
	ll maxn = 0;
	for(int i = 1; i <= n; ++i) {
		maxn = max(maxn, dp[i]);
	}
	printf("%lld\n", maxn);
	return 0;
}