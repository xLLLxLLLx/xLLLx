#include<bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10, LOG = 19;
struct data{
	int fr, nt, to;
	long long w;
}a[N << 1][2];
int n, m, t;
int cnt[2], res = 0, H = 0; 
int head[N][2], f[N], dfn[N], low[N];
int dep[N], h[N], g[N][LOG + 1];
int d[N][LOG + 1], dis[N], len[N];

void add(int id, int x, int y, int w) {
	// printf("%d %d %d %d\n",id,x,y,w);
	a[++cnt[id]][id].to = y;
	a[cnt[id]][id].fr = x;
	a[cnt[id]][id].w = w;
	a[cnt[id]][id].nt = head[x][id];
	head[x][id] = cnt[id];
}

void get(int x, int y, int id) {
	len[++H] = dis[y] - dis[x] + a[id][0].w;
	int tmp = y;
	for(;;) {
		h[tmp] = H;
		long long pos = min(dis[tmp] - dis[x], len[H] - dis[tmp] + dis[x]);
		if(tmp == x) {
			break;
		}
		add(1, tmp, x, pos);
		add(1, x, tmp, pos);
		tmp = a[f[tmp]][0].fr;
	}
}

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++res;
	for(int i = head[u][0]; i; i = a[i][0].nt) {
		int to = a[i][0].to;
		if(to == fa) {
			continue;
		}
		if(dfn[u] == low[to]) {
			get(u, to, i);
		} else if(dfn[to] == 0) {
			f[to] = i;
			dis[to] = dis[u] + a[i][0].w;
			dfs(to, u);
			if(low[to] > dfn[u]) {
				add(1, to, u, a[i][0].w);
				add(1, u, to, a[i][0].w);
			} 
			low[u] = min(low[u], low[to]);
		} else {
			low[u] = min(low[u], dfn[to]);
		}
	}
}

void Dfs(int u, int fa) {
	g[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for(int i = head[u][1]; i; i = a[i][1].nt) {
		int to = a[i][1].to;
		if(to == fa) {
			continue;
		}
		d[to][0] = a[i][1].w;
		Dfs(to, u);
	}
}

void yyqx() {
	for(int j = 1; j <= LOG; ++j) 
	 for(int i = 1; i <= n; ++i) {
	 	g[i][j] = g[g[i][j - 1]][j - 1];
	 	d[i][j] = d[i][j - 1] + d[g[i][j - 1]][j - 1];
	 }
}

int work(int x, int y) {
	if(dep[x] > dep[y]) {
		swap(x,y);
	}
	int ans=0;
	for(int j = LOG; j >= 0; --j) {
		if(dep[g[y][j]] >= dep[x]) {
			ans += d[y][j];
			y = g[y][j];
		}
	}
	if(x == y) {
		return ans;
	}
	for(int j = LOG; j >= 0; --j) {
		if(g[x][j] != g[y][j]) {
			ans += d[x][j] + d[y][j];
			x = g[x][j];
			y = g[y][j];
		}
	}
	if(h[x] && h[x] == h[y]) {
		return (ans + min(abs(dis[x] - dis[y]), len[h[x]] - abs(dis[x] - dis[y])));
	} else {
		return ans + d[x][0] + d[y][0];
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &t);
	for(int i = 1, x, y, w; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &w);
		add(0, x, y, w);
		add(0, y, x, w);
	}
	dfs(1, 0);
	Dfs(1, 0);
	yyqx();
	for(int i = 1, x, y; i <= t; ++i) {
		scanf("%d%d", &x, &y);
		printf("%d\n", work(x, y));
	}
	return 0;
}