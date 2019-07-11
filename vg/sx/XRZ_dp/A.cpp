#include<bits/stdc++.h>
using namespace std;
const int N = 6e4 + 10;
struct data {
	int nt, to;
}a[N << 1];
int cnt = 0, res = 0;
int dfn[N], low[N], head[N], vis[N], f[N], dp[N][2];

void add(int x, int y) {
	a[++cnt].to = y, a[cnt].nt = head[x], head[x] = cnt;
	a[++cnt].to = x, a[cnt].nt = head[y], head[y] = cnt;
}

int c[2], d[2];

void go(int x, int y) {
	int tmp = y;
	for(; tmp != x;) {
		int ff = f[tmp];
		d[0] = dp[ff][0], d[1] = dp[ff][1];
		d[0] += max(c[1], c[0]);
		d[1] += c[0];
		tmp = ff;
		c[0] = d[0], c[1] = d[1];
	}
}

void get(int x, int y) {
	c[0] = 0, c[1] = dp[y][1]; //tail is true
	go(x, y);
	int maxn = c[0];
	c[0] = dp[y][0], c[1] = 0; //tail is false
	go(x, y);
	dp[x][1] = c[1];
	dp[x][0] = max(maxn, c[0]);
}

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++res;
	vis[u] = 1, f[u] = fa;
	dp[u][1] = 1;
	for (int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if (to == fa) {
			continue;
		}
		if (dfn[u] == low[to]) {
			get(u, to);
		} else if (vis[to] == 0) {
			dfs(to, u);
			if (low[to] > dfn[u]) {
				dp[u][0] += max(dp[to][1], dp[to][0]);
				dp[u][1] += dp[to][0];
			}
			low[u] = min(low[u], low[to]);
		} else {
			low[u] = min(low[u], dfn[to]);
		}
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; ++i) {
		int x, y;
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1, 0);
	// for(int i = 1; i <= n; ++i) {
	// 	printf("dp[%d][0]=%d,dp[%d][1]=%d\n", i, dp[i][0], i, dp[i][1]);
	// }
	printf("%d\n", max(dp[1][0], dp[1][1]));
	return 0;
}