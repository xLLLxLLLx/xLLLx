#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
struct data {
	int nt, to;
} a[N << 1][2];
int n, m, n1;
ll ans = 0;
int top = 0, res = 0, tot = 0;
int head[N][2], cnt[2], dfn[N], low[N], st[N], sz[N], d[N];

void add(int id, int x, int y) {
	a[++cnt[id]][id].to = y;
	a[cnt[id]][id].nt = head[x][id];
	head[x][id] = cnt[id];
}

void dfs(int u, int fa) {
	tot++;
	st[++top] = u;
	dfn[u] = low[u] = ++res;
	for (int i = head[u][0]; i; i = a[i][0].nt) {
		int to = a[i][0].to;
		if (to == fa) {
			continue;
		}
		if (!dfn[to]) {
			dfs(to, u);
			if (low[to] >= dfn[u]) {
				++n1;
				add(1, n1, u);
				add(1, u, n1);
				d[n1]++;
				for (;;) {
					add(1, n1, st[top]);
					add(1, st[top], n1);
					d[n1]++;
					if (st[top] == to) {
						top--;
						break;
					}
					top--;
				}
			}
			low[u] = min(low[u], low[to]);
		} else {
			low[u] = min(low[u], dfn[to]);
		}
	}
}

void cal(int x, int y) {
	// printf("cal %d %d\n", x, y);
	ll now = 0;
	sz[x] = (x <= n);
	for (int i = head[x][1]; i; i = a[i][1].nt) {
		int to = a[i][1].to;
		if (to == y) {
			continue;
		}
		cal(to, x);
		if (x <= n) {
			ans += 1ll * sz[to] * now;
		} else {
			ans += 1ll * sz[to] * now * (d[x] - 2);
		}
		now += sz[to], sz[x] += sz[to];
	}
	if (y) {
		if (x <= n) {
			ans += now * (tot - sz[x]);
		} else {
			ans += now * (tot - sz[x]) * (d[x] - 2);
		}
	}
}

int main() {
	scanf("%d%d", &n, &m);
	n1 = n;
	for (int i = 1, x ,y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		add(0, x, y);
		add(0, y, x);
	}
	for (int i = 1; i <= n; ++i) {
		if (!dfn[i]) {
			tot = 0;
			dfs(i, 0);
			cal(i, 0);
		}
	}
	printf("%lld\n", ans * 2);
	return 0;
}