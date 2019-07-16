#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
struct data {
	int nt, to;
} a[N];
int head[N], d[N], vis[N], c[N], b[N], g[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y);
	}
	for(int u = 1; u <= n; ++u) {
		if(!vis[u]) {
			vis[u] = 2;
			b[++b[0]] = u;
			for(int i = head[u]; i; i = a[i].nt) {
				int to = a[i].to;
				vis[to] = max(vis[to], 1);
			}
		}
	}
	for(int u = n; u >= 1; --u) {
		if(vis[u] == 2) {
			c[++c[0]] = u;
			for(int i = head[u]; i; i = a[i].nt) {
				vis[a[i].to] = 1;
			}
		}
	}
	printf("%d\n", c[0]);
	for(int i = 1; i <= c[0]; ++i) {
		printf("%d ", c[i]);
	}
	return 0;
}