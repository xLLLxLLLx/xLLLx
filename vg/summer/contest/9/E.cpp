#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 710;
struct data {
	int nt, to;
} a[N];
int ans = 0, cnt = 0, res = 0;
int head[N], w[N], f[M][M], bl[N], fa[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int dfs(int x) {
	int d = 1, ch = 0;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		d = max(d, dfs(to) + 1);
		if(bl[to]) bl[x] = bl[to], ++ch;
	}
	if(d > s || ch > 1) {
		la[bl[x] = ++cnt] = x, d = 1;
		for(int i = head[x]; i; i = nxt[i]) pa[last[bl[to[i]]]] = x;
	}
	++sz[bl[x]];
	return d;
}

void Add(int x, int d) {
	int y = bl[x], z = sz[y], *v = f[y] + z;
	if(y && a[x] >= -z && a[x] < z) v[a[x]] += t;
	if(a[x] - lz[y] < 0) ans += t;
}

void upd(int 

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	s = sqrt(n);
	for(int i = 2; i <= n; ++i) {
		scanf("%d", &fa[i]);
		add(fa[i], i);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	dfs(1);
	for(int i = 1; i <= res; ++i) {
		int *v = f[i] + sz[i];
		for(int j = last[i]; bl[j] == bl[last[i]]; j = fa[j]) {
			if(a[j] >= -sz[i] && a[j] < sz[i]) ++v[a[j]];
		}
	}
	for(int i = 1, x; i <= m; ++i) {
		scanf("%d", &x);
		change(abs(x));
		printf("%d\n", ans);
	}
	return 0;
}