#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
struct data {
	int nt, to;
} a[N];
int head[N], vis[N], d[N], c[N], b[N], g[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int x) {
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(vis[to]) {
			continue;
		}
		vis[to] = 1;
		g[++g[0]] = to;
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		d[y]++;
		add(x, y);
	}
	for(int i = 1; i <= n; ++i) {
		if(!d[i]) c[++c[0]] = i, b[++b[0]] = i;
	}
	if(!c[0]) {
		c[++c[0]] = b[++b[0]] = 1;
		vis[1] = 1;
	}
	for(;;) {
		for(int j = 1; j <= 2; ++j) {
			g[0] = 0;
			for(int i = 1; i <= b[0]; ++i) {
				dfs(b[i]);
			}
			for(int i = 0; i <= g[0]; ++i) {
				b[i] = g[i];
			}
		}
		if(!b[0]) break;
		for(int i = 1; i <= b[0];++i) {
			c[++c[0]] = b[i];
		}
	}
	printf("%d\n", c[0]);
	for(int i = 1; i <= c[0]; ++i) {
		printf("%d ", c[i]);
	}
	return 0;
}