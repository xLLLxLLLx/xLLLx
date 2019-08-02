#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, LOG = 20;
struct data {
	int nt, to;
} a[N];
char lx[3];
int dfn[N], head[N], tp[N], sz[N], dep[N], g[N][LOG + 1];
int n ,m, cnt = 0, res = 0;

struct node {
	int v;
	bool operator < (const node &A) const {
		return dfn[v] < dfn[A.v];
	}
};
set<node> s[N];
int val[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	g[u][0] = fa;
	dfn[u] = ++res, dep[u] = dep[fa] + 1;
	int son = 0;
	for(int i = head[u]; i; i = a[i].nt) {
		son++;
		int to = a[i].to;
		tp[to] = tp[u];
		dfs(to, u);
		sz[u] += sz[to];
	}
	if(!son) sz[u] = 1;
}

void yyqx() {
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= n; ++i)
			g[i][j] = g[g[i][j - 1]][j - 1];
}

int GetLCA(int A, int B) {
	if(dep[A] > dep[B]) swap(A, B);
	for(int i = LOG; i >= 0; --i) 
		if(dep[g[B][i]] >= dep[A]) B = g[B][i];
	if(A == B)
		return A;
	for(int i = LOG; i >= 0; --i)
		if(g[A][i] != g[B][i])
			A = g[A][i], B = g[B][i];
	return g[A][0];
}

int main() {
	freopen("gangsters.in", "r", stdin);
	freopen("gangsters.out", "w", stdout);
	scanf("%d%d", &n, &m);
	for(int i = 2, x; i <= n; ++i) {
		scanf("%d", &x);
		add(x, i);
	}
	dep[1] = 1;
	for(int i = head[1]; i; i = a[i].nt) {
		tp[a[i].to] = a[i].to;
		dfs(a[i].to, 1);
	}
	yyqx();
	int now = 0, sum = 0, tot = 0;
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%s%d", lx + 1, &x);
		if(val[tp[x]]) tot--;
		if(lx[1] == '+') {
			now++;
			s[tp[x]].insert((node){x});
			int u = (*s[tp[x]].begin()).v, v = (*s[tp[x]].rbegin()).v;
			int lca = GetLCA(u, v);
			// printf("%d %d %d\n", u, v, lca);
			sum -= sz[val[tp[x]]];
			val[tp[x]] = lca;
			sum += sz[lca];
		} else {
			now--;
			s[tp[x]].erase(s[tp[x]].find((node){x}));
			int lca = 0;
			if(s[tp[x]].size()) {
				int u = (*s[tp[x]].begin()).v, v = (*s[tp[x]].rbegin()).v;
				lca = GetLCA(u, v);
			}
			sum -= sz[val[tp[x]]];
			val[tp[x]] = lca;
			sum += sz[lca];
		}
		if(val[tp[x]]) tot++;
		printf("%d %d\n", tot, sum - now);
	}
	return 0;
}