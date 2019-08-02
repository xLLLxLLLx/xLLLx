#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
ll ans;
int sz[N], vis[N], head[N], col[N], sum[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

ll js(ll x) {
	return x * (x - 1) / 2;
}

void dfs(int u, int fa) {
	sz[u] = 1;
	int son = 0;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		int last = sum[col[u]];
		dfs(to, u);
		sz[u] += sz[to];
		int now = sum[col[u]] - last;
		ans -= js(sz[to] - now);
		son += sz[to] - now;
	}
	sum[col[u]] += son + 1;
}

int main() {
	int n, cas = 0;
	while(scanf("%d", &n) == 1) {
		cnt = ans = 0;
		int tot = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &col[i]);
			if(!vis[col[i]]) {
				tot++, vis[col[i]] = 1;
			}
		}
		for(int i = 1, x, y; i < n; ++i) {
			scanf("%d%d", &x, &y);
			add(x, y), add(y, x);
		}
		ans = 1ll * tot * js(n);
		dfs(1, 0);
		for(int i = 1; i <= n; ++i) {
			head[i] = 0;
			if(vis[col[i]]) {
				// printf("%d %d\n", col[i], sum[col[i]]);
				ans -= js(n - sum[col[i]]);
				vis[col[i]] = 0;
				sum[col[i]] = 0;
			}
		}
		++cas;
		printf("Case #%d: %lld\n", cas, ans);
	}
	return 0;
}