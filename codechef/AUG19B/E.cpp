#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, M = 2e6 + 10;
ll val[M];
int a[N], qz[N], nm[M];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		memset(nm, 0, sizeof nm);
		memset(val, 0, sizeof val);
		int n;
		scanf("%d", &n);
		qz[0] = 0;
		ll ans = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			if(i > 1) 
				nm[qz[i - 2]]++, val[qz[i - 2]] += i - 1;
			qz[i] = qz[i - 1] ^ a[i];
			ans += 1ll * nm[qz[i]] * i - val[qz[i]];
		}
		printf("%lld\n", ans);
	}
	return 0;
}