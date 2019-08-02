#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 55, mod = 1e9 + 7;
int n, k;
int all[N], fl[N], de[N], nm[N], fb[N][N], r[N], pd[N], w[N];
ll f[N][N], dp[N][N], tmp = 0;

void init() {
	for(int i = 0; i < N; ++i) f[i][i] = f[i][0] = 1;
	for(int i = 1; i < N; ++i)
		for(int j = 1; j < i; ++j)
			f[i][j] = (f[i - 1][j - 1] + f[i - 1][j]) % mod;
}

ll gao(int z, int num) {
	int tot = 0;
	for(int i = 1; i <= 50; ++i) {
		int pos = min(k - r[i], fb[i][z]);
		w[++tot] = pos;
	}
	dp[0][0] = 1;
	for(int i = 1; i <= tot; ++i) {
		for(int j = 0; j <= num; ++j) {
			for(int k = 0; k <= min(w[i], num - j); ++k) {
				dp[i][j + k] += dp[i - 1][j] * f[fb[i][z]][k] % mod;
				dp[i][j + k] %= mod;
			}
		}
	}
	return dp[tot][num];
}

int main() {
	init();
	scanf("%d%d", &n, &k);
	int gg = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &fl[i]);
		pd[fl[i]]++;
	}
	for(int i = 1; i <= 50; ++i) {
		gg += min(pd[i], k);
	}
	if(gg < 2 * k) {
		puts("-1");
		exit(0);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &de[i]);
		all[i] = de[i];
	}
	sort(all + 1, all + 1 + n);
	int m = unique(all + 1, all + 1 + n) - all - 1;
	for(int i = 1; i <= n; ++i) {
		de[i] = lower_bound(all + 1, all + 1 + m, de[i]) - all;
		nm[de[i]]++;
		fb[fl[i]][de[i]]++;
	}
	int ans = 0, kk = 0;
	ll fang = 1;
	for(int i = m; i >= 1; --i) {
		int now = 0;
		ll pos = 1;
		for(int j = 1; j <= 50; ++j) {
			if(r[j] >= k) continue;
			now += min(k - r[j], fb[j][i]);
			if(fb[j][i] > k - r[j]) pos = pos * f[fb[j][i]][k - r[j]] % mod;
		}
		if(now + kk >= 2 * k) {
			ans += (2 * k - kk) * all[i];
			fang  = fang * gao(i, 2 * k - kk) % mod;
			break;
		} else {
			ans += now * all[i];
			fang = fang * pos % mod;
			for(int j = 1; j <= 50; ++j) {
				r[j] += min(k - r[j], fb[j][i]);
			}
		}
		kk += now;
	}
	printf("%d %lld\n", ans, fang);
	return 0;
}