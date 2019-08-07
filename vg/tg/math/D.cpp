#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 22;
ll dp[N][N];
int qx[N], cnt = 0;

ll search(int len, int lmt, int num, int f) {
	if(!len) {
		return f ? 1ll : (long long)num;
	}
	if(dp[len][num] != -1 && !lmt && !f) return dp[len][num];
	ll sum = 0;
	int up = lmt ? qx[len] : 9;
	for(int i = 0; i <= up; ++i) {
		if(f){
			sum += search(len - 1, (i == up) && lmt, num, i == 0);
		} else {
			sum += search(len - 1, (i == up) && lmt, num + (i == 0), 0);
		}
	}
	if(lmt || f) return sum;
	else return dp[len][num] = sum;
}

ll get(ll x) {
	if(x == -1) return 0ll;
	cnt = 0;
	for(; x; x /= 10) qx[++cnt] = x % 10;
	ll pos = search(cnt, 1, 0, 1);
	// printf("%lld\n", pos);
	return pos;
}

int main() {
	int T;
	scanf("%d", &T);
	memset(dp, -1, sizeof dp);
	for(int o = 1; o <= T; ++o) {
		ll l, r;
		scanf("%lld%lld", &l, &r);
		printf("Case %d: %lld\n", o, get(r) - get(l - 1));
	}
	return 0;
}