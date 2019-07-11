#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
vector <int> g[N];
int w[N];
int tp = 0, c = 0, st[N], d[N];
int dfn[N], low[N], vis[N], col[N];
int head[N], res = 0, cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int x) {
	vis[x] = 1, st[++tp] = x;
	low[x] = dfn[x] = ++res;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(vis[to]) {
			low[x] = min(low[x], dfn[to]);
		} else if(!dfn[to]) {
			dfs(to);
			low[x] = min(low[x], low[to]);
		}
	}
	if(dfn[x] == low[x]) {
		vis[x] = 0, col[x] = ++c;
		for(;st[tp] != x; tp--) {
			int pos = st[tp];
			vis[pos] = 0;
			col[pos] = c;
			g[c].push_back(pos);
		}
		g[c].push_back(st[tp--]);
	}
}


int main() {
	int n, m, h;
	scanf("%d%d%d", &n, &m, &h);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		if((w[x] + 1) % h == w[y]) add(x, y);
		if((w[y] + 1) % h == w[x]) add(y, x);
	}
	for(int i = 1; i <= n; ++i) {
		if(!dfn[i]) {
			dfs(i);
		}
	}
	for(int u = 1; u <= n; ++u) {
		// printf("%d\n", col[u]);
		for(int i = head[u]; i; i = a[i].nt) {
			int to = a[i].to;
			if(col[u] != col[to]) {
				d[col[u]]++;
			}
		}
	}
	int ans = n + 1, be = 0;
	for(int i = 1; i <= c; ++i) {
		if(!d[i]) {
			int len = g[i].size();
			if(ans > len) {
				ans = len, be = i;
			}
		}
	}
	printf("%d\n", ans);
	for(int i = 0; i < ans; ++i) {
		printf("%d ", g[be][i]);
	}
	return 0;
}