#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 15;
ll maxn = 1e18;

int a[N], b[N];

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = ans * x;
		x = x * x;
	}
	return ans;
}

void dfs(int dep, int now, int last) {
	if(now >= 999) {
		ll pos = 1;
		// for(int i = 1; i <= dep - 1; ++i) {
		// 	printf("%d ", b[i]);
		// }
		// puts("");
		for(int i = 1; i <= dep - 1; ++i) {
			pos = pos * q_pow(a[i], b[i]);
		}
		if(pos == 245044800) {
			for(int i = 1; i <= dep - 1; ++i) {
				printf("%d ", b[i]);
			}
			puts("");
		}
		maxn = min(maxn, pos);
		return ;
	}
	if(dep > 10) return;
	for(int i = 1; i <= last; ++i) {
		b[dep] = i;
		dfs(dep + 1, (i + 1) * now, i);
		if((i + 1) * now >= 1000) break;
	}
}

int main() {
	for(int i = 1; i <= 10; ++i) {
		scanf("%d", &a[i]);
	}
	dfs(1, 1, 20);
	printf("%lld\n", maxn);
	return 0;
}