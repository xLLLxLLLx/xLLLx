#include <bits/stdc++.h>
using namespace std;
const int N = 5e4 + 10;
vector<int> g[N];
int f[N], w[N];

int bz, maxn = 0;

void dfs(int u, int fa) {
	int son = 0, pos = 0;
	f[u] = (w[u] >= bz);
	for(int i = 0; i < g[u].size(); ++i) {
		int to = g[u][i];
		if(to == fa) continue;
		dfs(to, u);
		son++;
		if(w[to] >= bz && w[u] >= bz) {
			f[u] = max(f[u], pos + f[to] + 1);
			pos = max(pos, f[to]);
		}
	}
	if(!son) f[u] = (w[u] >= bz);
	maxn = max(maxn, f[u]);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		g[x].push_back(y);
		g[y].push_back(x);
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i) {
		memset(f, 0, sizeof f);
		bz = w[i];
		maxn = 0, dfs(1, 0);
		// if(bz == 33852) printf("max%d\n",maxn);
		ans = max(ans, maxn * w[i]);
	}
	printf("%d\n", ans);
	return 0;
}