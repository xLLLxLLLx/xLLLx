#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, LOG = 20;
queue<int> Q;
int n, m;
int d[N], tp[N], dep[N], f[N][LOG + 1];
vector <int> g[N], t[N];

void read(int &x) {
	char ch = getchar(); x = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) ;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

int GetLCA(int a, int b) {
	if(dep[a] > dep[b]) swap(a, b);
	for(int i = LOG; i >= 0; --i)
		if(dep[f[b][i]] >= dep[a]) b = f[b][i];
	if(a == b)
		return a;
	for(int i = LOG; i >= 0; --i)
		if(f[a][i] != f[b][i])
			a = f[a][i], b = f[b][i];
	return f[a][0];
}

int main() {
	int T;
	read(T);
	for(int o = 1; o <= T; ++o) {
		read(n), read(m);
		for(int i = 1; i <= n + 1; ++i) {
			g[i].clear(), t[i].clear();
			d[i] = dep[i] = 0;
			for(int j = 0; j <= LOG; ++j)
				f[i][j] = 0;
		}
		for(int i = 1, x, y; i <= m; ++i) {
			read(x), read(y);
			g[x].push_back(y), t[y].push_back(x);
			d[x]++;
		}
		int ed = n + 1;
		dep[ed] = 1;
		for(int i = 1; i <= n; ++i) {
			if(!d[i]) {
				Q.push(i);
				g[i].push_back(ed), t[ed].push_back(i);
			}
		}
		int cnt = 0;
		while(!Q.empty()) {
			int h = Q.front(); Q.pop();
			tp[++cnt] = h;
			for(int i = 0; i < t[h].size(); ++i) {
				if(!(--d[t[h][i]])) {
					Q.push(t[h][i]);
				}
			}
		}
		for(int i = 1; i <= cnt; ++i) {
			int u = tp[i], fa = -1;
			for(int j = 0; j < g[u].size(); ++j) 
				fa = (fa == -1) ? g[u][j] : GetLCA(fa, g[u][j]);
			dep[u] = dep[fa] + 1, f[u][0] = fa;
			for(int j = 1; j <= LOG; ++j)
				f[u][j] = f[f[u][j - 1]][j - 1];
		}
		int q;
		read(q);
		for(int i = 1, x, y; i <= q; ++i) {
			read(x), read(y);
			int lca = GetLCA(x, y);
			printf("%d\n", dep[x] + dep[y] - dep[lca] - 1);
		}
	}
	return 0;
}