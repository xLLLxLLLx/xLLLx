#include <bits/stdc++.h>
const int N = 2e5 + 10, LOG = 19;
using namespace std;
struct data {
	int to, nt, id, w;
} ed[N], a[N << 1];
int n, m, cnt = 0;
int v[N][LOG + 1], ans[N];
int dep[N], ys[N], g[N][LOG + 1], head[N];
int f[N], used[N];

bool cmp(data A, data B) {
	return A.w < B.w;
}

void add(int x, int y, int id, int w) {
	a[++cnt].to = y;
	a[cnt].id = id;
	a[cnt].w = w;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int find(int k) {
	return k == f[k] ? f[k] : f[k] = find(f[k]);
}

void kruskal() {
	sort(ed + 1, ed + 1 + m, cmp);
	for(int i = 1; i <= n; ++i) f[i] = i;
	int now = 0;
	for(int i = 1; i <= m; ++i) {
		int fx = find(ed[i].to), fy = find(ed[i].nt);
		if(fx != fy) {
			now++;
			used[i] = 1;
			f[fx] = fy;
			// printf("%d %d %d\n", ed[i].to, ed[i].nt, ed[i].w);
			add(ed[i].to, ed[i].nt, ed[i].id, ed[i].w);
			add(ed[i].nt, ed[i].to, ed[i].id, ed[i].w);
		}
		if(now == n - 1) return ;
	}
}

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	g[u][0] = fa;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
		v[to][0] = a[i].w;
		ys[to] = a[i].id;
	}
}

void yyqx() {
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= n; ++i) {
			g[i][j] = g[g[i][j - 1]][j - 1];
			v[i][j] = max(v[i][j - 1], v[g[i][j - 1]][j - 1]);
		}
}

int GetLCA(int A, int B, int &val) {
	val = 0;
	if(dep[A] > dep[B]) swap(A, B);
	for(int i = LOG; i >= 0; --i)
		if(dep[g[B][i]] >= dep[A]) {
			val = max(val, v[B][i]);
			B = g[B][i];
		}
	if(A == B) return A;
	for(int i = LOG; i >= 0; --i) 
		if(g[A][i] != g[B][i]) {
			val = max(val, max(v[A][i], v[B][i]));
			A = g[A][i], B = g[B][i];
		}
	val = max(val, max(v[A][0], v[B][0]));
	return g[A][0];
} 

void change(int x, int y, int val) {
	// printf("val=%d\n", val);
	x = find(x);
	while(dep[x] > dep[y]) {
		ans[ys[x]] = min(ans[ys[x]], val);
		int y = find(g[x][0]);
		f[x] = y;
		x = find(x);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d%d", &ed[i].to, &ed[i].nt, &ed[i].w);
		ed[i].id = i;
	}
	kruskal();
	dfs(1, 0), yyqx();
	// for(int i = 1; i <= n; ++i) 
	//  for(int j = 0; j <= LOG; ++j) {
	// 	printf("v[%d][%d] = %d\n", i, j, v[i][j]);
	// }
	for(int i = 1; i <= m; ++i) f[i] = i;
	for(int i = 1; i <= m; ++i) ans[i] = 1e9;
	for(int i = 1; i <= m; ++i) {
		if(used[i]) continue;
		int u = ed[i].nt, v = ed[i].to;
		int lca = GetLCA(u, v, ans[ed[i].id]);
		// printf("qwq%d %d %d %d\n", u, v, lca, ans[ed[i].id]);
		ans[ed[i].id]--;
		change(u, lca, ed[i].w - 1), change(v, lca, ed[i].w - 1);
	}
	for(int i = 1; i <= m; ++i) {
		if(ans[i] == 1e9) ans[i] = -1;
		printf("%d ", ans[i]);
	}
	return 0;
}

/*
10 21
5 6 88
6 3 74
1 5 7
1 6 27
8 1 50
4 1 24
10 6 37
9 7 39
5 7 63
2 7 98
3 4 28
9 2 5
2 4 96
9 6 67
9 10 47
10 4 64
2 5 70
6 8 89
3 5 54
6 7 18
1 7 26

25 27 53 25 88 53 46 46 25 38 53 69 38 38 38 36 38 49 27 26 26 
*/