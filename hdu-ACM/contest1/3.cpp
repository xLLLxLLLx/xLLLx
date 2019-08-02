#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e4 + 10;
struct data {
	int r, c, t;
} a[N];
vector<int> g[N];
ll dp[N], f[N], tmp[N], res[N];
int all[N], pos;

bool cmp(int x, int y) {
	if(a[x].c < pos) {
		if(a[y].c > pos) return 1;
		else return a[x].c > a[y].c;
	} else {
		if(a[y].c < pos) return 0;
		else return a[x].c < a[y].c;
	}
}

bool comp(int x, int y) {
	return a[x].c < a[y].c;
}

void qk(int k) {
	for(int i = 1; i <= k; ++i) {
		tmp[i] = res[i] = 1e18;
	}
}

void Min(ll &x, ll y) {
	x = min(x, y);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		pos = (1 + m) / 2;
		for(int i = 1; i <= k; ++i) {
			scanf("%d%d%d", &a[i].r, &a[i].c, &a[i].t);
			all[i] = a[i].r;
		}
		sort(all + 1, all + 1 + n);
		int tot = unique(all + 1, all + 1 + n) - all - 1;
		for(int i = 1; i <= n; ++i) {
			g[i].clear();
		}
		for(int i = 1; i <= n; ++i) {
			a[i].r = lower_bound(all + 1, all + 1 + tot, a[i].r) - all;
			g[a[i].r].push_back(i);
		}
		for(int i = 1; i <= n; ++i) {
			dp[i] = f[i] = 1e18;
		}
		int now = 1;
		ll qz = 0;
		qk(k);
		for(int i = 0; i < g[1].size(); ++i) {
			for(int j = 0; j < k; ++j) {
				Min(dp[j + 1], dp[j] + g[1][i].t);
				Min(tmp[j + 1], dp[j + 1] + g[1][i].c + abs(g[1][i].c - pos));
				Min(res[j + 1], dp[j + 1] + g[1][i].c);
			}
		}
		for(int i = 1; i <= k; ++i) {
			min(f[i], res[i]);
			dp[i] = tmp[i];
		}
		now = 2;
		for(int i = 1; i <= k; ++i) {
			printf("%lld ", f[i]);
		}
		puts("");
	}
	return 0;
}