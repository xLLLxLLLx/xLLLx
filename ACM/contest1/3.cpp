#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N][2];
int head[N][2], cnt[2], vis[N], vs[N];

void add(int x, int y, int id) {
	a[++cnt[id]][id].to = y;
	a[cnt[id]][id].nt = head[x][id];
	head[x][id] = cnt[id];
}

void dfs(int x, int id) {
	vs[x] = 1;
	for(int i = head[x][id]; i; i = a[i][id].nt) {
		int to = a[i][id].to;
		if(!vs[to]) {
			vis[i]++;
			dfs(to, id);
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m;
		cnt[0] = cnt[1] = 0;
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) 
			head[i][0] = head[i][1] = 0;
		for(int i = 1, x, y; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			vis[i] = 0;
			add(x, y, 0);
			add(y, x, 1);
		}
		for(int i = 1; i <= n; ++i)
			vs[i] = 0;
		dfs(1, 0);
		for(int i = 1; i <= n; ++i) 
			vs[i] = 0;
		dfs(1, 1);
		int now = m - 2 * n;
		// for(int i = 1; i <= m; ++i) {
		// 	printf("%d %d\n", i, vis[i]);
		// }
		for(int u = 1; u <= n; ++u) {
			for(int i = head[u][0]; i; i = a[i][0].nt) {
				if(!vis[i] && now) {
					printf("%d %d\n", u, a[i][0].to);
					now--;
				}
			}
		}
	}
	return 0;
}