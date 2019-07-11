#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10, M = 2e4 + 10, MASK = 3010;
struct data {
	ll w, e;
} a[N];
vector<ll> g[N];
int c[N];
ll yz[20], b[N], all[N], f[20][MASK];

ll get(ll A, ll B) {
	return B ? get(B, A % B) : A;
}

int main() {
	int n;
	ll k;
	scanf("%d%lld", &n, &k);
	ll gcd = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i].w);
		gcd = get(gcd, a[i].w);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i].e);
	}
	int len = sqrt(gcd), res = 0;
	ll now = gcd;
	for(int i = 2; i <= len; ++i) {
		if(now % i == 0) {
			yz[res++] = i;
			while(now % i == 0) {
				now /= i;
			}
		}
	}
	if(now > 1) {
		yz[res++] = now;
	}
	for(int i = 1; i <= n; ++i) {
		b[i] = 1;
		for(int j = 0; j < res; ++j) {
			if(a[i].w % yz[j] == 0) {
				while(a[i].w % yz[j] == 0) {
					a[i].w /= yz[j];
					b[i] *= yz[j];
				}
			}
		}
		all[i] = b[i];
	}
	sort(all + 1, all + 1 + n);
	int m = unique(all + 1, all + 1 + n) - all - 1;
	for(int i = 1; i <= n; ++i) {
		b[i] = lower_bound(all + 1, all + 1 + m, b[i]) - all;
		g[b[i]].push_back(a[i].e);
	}
	memset(f, 0x3f, sizeof f);
	f[0][0] = 0;
	int tot = (1 << res) - 1;
	for(int o = 1; o <= m; ++o) {
		ll tmp = all[o];
		c[0] = 0;
		for(int j = 0; j <= tot; ++j) {
			ll pos = 1;
			tmp = all[o];
			for(int k = 0; k < res; ++k) {
				if((j >> k) & 1) {
					while(tmp % yz[k] == 0) {
						tmp /= yz[k];
						pos *= yz[k];
					}
				}
			}
			if(pos <= k) c[++c[0]] = j;
		}
		sort(g[o].begin(), g[o].end());
		int l = min((int)g[o].size(), res);
		for(int i = 0; i < l; ++i)
		 for(int k = res; k; --k)
		  for(int j = 1; j <= c[0]; ++j) {
		   for(int t = tot ^ c[j], s = t; ; s = (s - 1) & t) {
		   	f[k][s|c[j]] = min(f[k][s|c[j]], f[k - 1][s] + g[o][i]);
		   	if(!s) break;
		   }
		  }
	}
	ll ans = 1e18;
	// for(int i = 0; i <= res; ++i) {
	// 	for(int j = 0; j <= tot; ++j) {
	// 		if(f[i][j] != f[15][0]) {
	// 			printf("f[%d][%d]=%d\n", i, j, f[i][j]);
	// 		}
	// 	}
	// }
	for(int i = 0; i <= res; ++i) {
		if(f[i][tot] != f[15][0]) {
			ans = min(ans, f[i][tot] * i);
		}
	}
	if(ans == 1e18) {
		printf("-1\n");
	} else {
		printf("%lld\n", ans);
	}
	return 0;
}