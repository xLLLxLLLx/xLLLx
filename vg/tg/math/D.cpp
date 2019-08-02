#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 22;
ll dp[N];
int qx[N], cnt = 0;

ll search(int len, int lmt) {
	printf("len=%d lmt=%d\n", len, lmt);
	if(len == 1) {
		return dp[len] = 1;
	}
	if(dp[len] != -1 && !lmt) return dp[len];
	ll sum = 0;
	int up = lmt ? qx[len] : 9;
	for(int i = 0; i <= up; ++i) {
		sum += search(len - 1, (i == up) && lmt) + (i == 0);
	}
	if(lmt) return sum;
	else return dp[len] = sum;
}

ll get(ll x) {
	if(x == -1) return 0ll;
	cnt = 0;
	for(; x; x /= 10) qx[++cnt] = x % 10;
	ll pos = search(cnt, 1);
	printf("%lld\n", pos);
	return pos;
}

int main() {
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	for(int o = 1; o <= T; ++o) {
		ll l, r;
		scanf("%lld%lld", &l, &r);
		printf("%lld\n", get(r) - get(l - 1));
	}
	for(int i = 1; i <= 3; ++i) {
		if(dp[i] != -1) {
			printf("qwq%d %lld\n", i, dp[i]);
		}
	}
	return 0;
}