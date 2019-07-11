#include <bits/stdc++.h>
using namespace std;
const int N = 1e5, M = 6e6 + 10;
struct data {
	int nt, to;
} a[N + 10];
struct node {
	int l, r, mx;
	node() {
		l = r = mx = 0;
	}
} tr[M];
vector<int> g[N];
int head[N + 10], w[N + 10], d[N + 10], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void init() {
	for(int i = 1; i <= N; ++i) {
		int len = sqrt(i);
		for(int j = 1; j <= len; ++j) {
			if(i % j) {
				continue;
			}
			g[i].push_back(j);
			if(j * j != i) g[i].push_back(i / j);
		}
	}
}

void put(int x, int l, int r, int L) {
	if(l == r) {
		if(!tr[x].mx) {
			tr[x].mx = 1;
		}
	}
}

int merge(int A, int B) {
	if(!A) return B;
	if(!B) return A;
	int pos = ++now;
	tr[pos].l = merge(tr[A].l, tr[B].l);
	tr[pos].r = merge(tr[A].r, tr[B].r);
	tr[pos].mx = max(tr[tr[pos].l].mx, tr[tr[B].r].mx);
	return pos;
}

void dfs(int u, int fa) {
	rt[u] = ++now;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
		rt[u] = merge(rt[u], rt[to]);
	}
	int len = g[w[u]].size();
	for(int i = 0; i < len; ++i) {
		if(find(rt[u], 1, N, g[w[u]][i])) {
			d[u] = max(d[u], g[w[u]][i]);
		}
		put(rt[u], 1, N, g[w[u]][i]);
	}
}

int main() {
	int n;
	init();
	scanf("%d", &n);
	for(int i = 2, x; i <= n; ++i) {
		scanf("%d", &x);
		add(x, i);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	memset(d, -1, sizeof d);
	dfs(1, 0);
	for(int i = 1; i <= n; ++i) {
		printf("%d\n", d[i]);
	}
	return 0;
}