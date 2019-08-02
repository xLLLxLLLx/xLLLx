#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 1010;
struct data {
	int nt, to;
} g[N];
int n, m, cnt = 0, res = 0, block = 0;
int t[N], a[N], add[N], arr[M][M];
int dfn[N], fa[N], sz[N], s[N], tp[N], pos[N], head[N];

void Add(int x, int y) {
	g[++cnt].to = y;
	g[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs1(int x) {
	sz[x] = 1, s[x] = 0;
	for(int i = head[x]; i; i = g[i].nt) {
		dfs1(g[i].to);
		sz[x] += sz[g[i].to];
		if(sz[s[x]] < sz[g[i].to]) s[x] = g[i].to;
	}
}

void dfs2(int x, int top) {
	dfn[x] = ++res;
	tp[x] = top;
	if(s[x]) dfs2(s[x], top);
	for(int i = head[x]; i; i = g[i].nt) {
		if(g[i].to != s[x]) dfs2(g[i].to, g[i].to);
	}
}

void modify(int x) {
	arr[x][0] = 0;
	for(int i = (x - 1) * block + 1; pos[i] == x; ++i) {
		arr[x][++arr[x][0]] = a[i];
	}
	sort(arr[x] + 1, arr[x] + arr[x][0] + 1);
}

void change(int l, int r, int upd) {
	for(int i = pos[l] + 1; i < pos[r]; ++i) add[i] += upd;
	for(int i = l; pos[i] == pos[l] && i <= r; ++i) a[i] += upd;
	modify(pos[l]);
	if(pos[l] != pos[r]) {
		for(int i = r; pos[i] == pos[r] && i >= l; --i) a[i] += upd;
		modify(pos[r]);
	}
}

int getans() {
	int ans = 0;
	for(int i = 1; i <= pos[n]; ++i) {
		ans += arr[i][0] - (upper_bound(arr[i] + 1, arr[i] + arr[i][0] + 1, -add[i]) - arr[i]) + 1;
	}
	return ans;
}

int main() {
	scanf("%d%d", &n, &m);
	block = sqrt(n);
	for(int i = 2; i <= n; ++i) {
		scanf("%d", &fa[i]);
		Add(fa[i], i);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &t[i]);
		pos[i] = (i - 1) / block + 1;
	}
	dfs1(1), dfs2(1, 1);
	for(int i = 1; i <= n; ++i) {
		int gg = pos[dfn[i]];
		arr[gg][++arr[gg][0]] = a[dfn[i]] = -t[i];
	}
	// for(int i = 1; i <= n; ++i) {
	// 	printf("%d dfn=%d s=%d tp=%d\n", i, dfn[i], s[i], tp[i]);
	// }
	for(int i = 1; i <= pos[n]; ++i) sort(arr[i] + 1, arr[i] + arr[i][0] + 1);
	for(int i = 1, now; i <= m; ++i) {
		scanf("%d", &now);
		if(!now) {
			printf("%d ", getans());
			continue;
		}
		int fh = now > 0 ? 1 : (now = -now, -1);
		change(dfn[now], dfn[now], -fh * n);
		now = fa[now];
		while(now) {
			// printf("now = %d\n", now);
			change(dfn[tp[now]], dfn[now], fh);
      now = fa[tp[now]];
		}
		printf("%d ", getans());
	}
	return 0;
}