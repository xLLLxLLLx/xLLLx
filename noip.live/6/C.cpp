#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
vector<int> g[N], f[N];
vector<ll> c[N];
ll w[N];
int head[N], dfn[N], dep[N], ed[N], ys[N];
int res = 0, cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	dfn[u] = ++res, ys[res] = u;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa)
			continue;
		dfs(to, u);
	}
	ed[u] = res;
}

int find(int x, int k) {
	int l = 0, r = g[x].size() - 1, ans = r + 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(g[x][mid] > k) {
			ans = mid, r = mid - 1;
		} else {
			r = mid - 1;
		}
	}
	return ans;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; ++i) {
		int u = ys[i];
		g[dep[u]].push_back(i);
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j <= g[i].size(); ++j)
			c[i].push_back(0);
	}
	for(int i = 1, x, y, z; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &z);
		if(!y) {
			w[dfn[x]] += z;
		} else {
			int pos = dep[x] + y;
			// for(int j = 0; j < g[pos].size(); ++j)
			// 	printf("%d ", g[pos][j]);
			// puts("");
			// printf("dfn = %d ed = %d\n", dfn[x], ed[x]);
			int l = find(pos, dfn[x]);
			int r = find(pos, ed[x]);
			// printf("%d %d\n", l, r);
			c[pos][l] += z, c[pos][r] -= z;
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j < c[i].size(); ++j) {
			c[i][j] += c[i][j - 1];
		}
		for(int j = 0; j < g[i].size(); ++j) {
			w[g[i][j]] += c[i][j];
		}
	}
	for(int i = 1; i <= n; ++i) {
		printf("%lld ", w[dfn[i]]);
	}
	return 0;
}