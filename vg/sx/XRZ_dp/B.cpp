#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 1e5 + 10, M = 1e3 + 10;
struct data {
	int nt, to;
}a[N << 1];
int cnt = 0, res = 0, maxn = 0;
int head[N], dfn[N], dep[N], low[N], dp[N], f[N], e[M];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int c[N], d[N], len[N];

void get(int x, int y) {
	c[0] = 0;
	int tot = dep[y] - dep[x] + 1;
	int mxx = tot / 2;
	int tmp = y;
	for(;;) {
		c[++c[0]] = tmp;
		len[c[0]] = dep[tmp];
		if(tmp == x) {
			break;
		}
		tmp = f[tmp];
	}
	reverse(c + 1, c + 1 + c[0]);
	reverse(len + 1, len + 1 + c[0]);
	for(int i = 1; i <= c[0]; ++i) {
		c[c[0] + i] = c[i];
		len[c[0] + i] = len[i] + tot;
	}
	c[0] <<= 1;
	int l = 1, r = 0;
	for(int i = 1; i <= c[0]; ++i) {
		while(l <= r && len[i] - len[d[l]] > mxx) {
			l++;
		}
		if(l <= r) {
			maxn = max(maxn, dp[c[i]] + dp[c[d[l]]] + len[i] - len[d[l]]);
		}
		while(l <= r && dp[c[d[r]]] - len[d[r]] < dp[c[i]] - len[i]) {
			r--;
		}
		d[++r] = i;
	}
	for(int i = 1; i <= c[0]; ++i) {
		int pos = dep[c[i]] - dep[x];
		pos = min(pos, tot - pos);
		dp[x] = max(dp[x], dp[c[i]] + pos);
	}
}

void dfs(int u, int fa) {
	// printf("%d %d\n",u,fa);
	f[u] = fa;
	dep[u] = dep[fa] + 1;
	dfn[u] = low[u] = ++res;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		if (dfn[u] == low[to]) {
			get(u,to);
		} else if(dfn[to] == 0) {
			dfs(to, u);
			if(low[to] > dfn[u]) {
				maxn = max(maxn, dp[u] + dp[to] + 1);
				dp[u] = max(dp[u], dp[to] + 1);
			}
			low[u] = min(low[u], low[to]);
		} else {
			low[u] = min(low[u], dfn[to]);
		}
	}
}

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) == 2) {
		for(int o = 1, k; o <= m; ++o) {
			scanf("%d", &k);
			for(int i = 1; i <= k; ++i) {
				scanf("%d", &e[i]);
				if(i > 1) {
					add(e[i], e[i-1]);
					add(e[i-1], e[i]);
				}
			}
		}
		dfs(1, 0);
		for(int i = 1; i <= n; ++i) {
			maxn=max(maxn, dp[i]);
		}
		printf("%d\n", maxn);
		fill(dp + 1, dp + 1 + n, 0);
		fill(dfn + 1, dfn + 1 + n, 0);
		fill(low + 1, low + 1 + n, 0);
		fill(head + 1, head + 1 + n, 0);
		cnt = 0, res = 0, maxn = 0;
	}
	return 0;
}