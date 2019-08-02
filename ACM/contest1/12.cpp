#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 20;
struct Path {
	int len, u, v;
} b[N];
struct data {
	int nt, to;
} a[N << 1];
queue<int> q;
vector<int> G[N];
int cnt = 0, n, m;
int val[N], ys[N], sy[N], vis[N], st[N];
int d[N], head[N], dep[N], g[N][LOG + 1];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	g[u][0] = fa;
	dep[u] = dep[fa] + 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
	}
}

void Dfs(int u, int fa) {
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		Dfs(to, u);
		val[u] += val[to];
	}
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
	if(A == B) return A;
	for(int i = LOG; i >= 0; --i) 
		if(g[A][i] != g[B][i])
			A = g[A][i], B = g[B][i];
	return g[A][0];
}

bool cmp(Path A, Path B) {
	return A.len > B.len;
}

bool go(int be) {
	vis[be] = 1;
	q.push(be);
	int now = 0;
	while(!q.empty()) {
		int h = q.front(); q.pop();
		sy[h] = ++now, ys[now] = h;
		for(int i = head[h]; i; i = a[i].nt) {
			int to = a[i].to;
			if(!vis[to] && val[to]) {
				vis[to] = 1;
				q.push(to);
				break;
			}
		}
	}
	int top = 0;
	for(int i = 1; i <= now; ++i) {
		int h = ys[i];
		while(top && st[top] < i) top--;
		for(int j = 0; j < G[h].size(); ++j) {
			int to = G[h][j];
			if(sy[to] <= i) continue;
			if(!top || sy[to] <= st[top]) st[++top] = sy[to];
			else return false;
		}
	}
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(1, 0), yyqx();
	int tot = 0;
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		if(x == y) continue;
		int lca = GetLCA(x, y);
		// printf("%d %d %d\n", x, y, lca);
		b[++tot].u = x, b[tot].v = y, b[tot].len = dep[x] + dep[y] - 2 * dep[lca];
		val[x]++, val[y]++;
		val[lca] -= 1;
		val[g[lca][0]] -= 1;
	}
	Dfs(1, 0);
	for(int u = 1; u <= n; ++u) {
		if(val[u]) {
			for(int i = head[u]; i; i = a[i].nt) {
				int to = a[i].to;
				if(val[to]) {
					d[u]++;
				}
			}
		}
	}
	for(int i = 1; i <= n; ++i) {
		if(d[i] > 2) return printf("No\n"), 0;
	}
	sort(b + 1, b + 1 + tot, cmp);
	for(int i = 1; i <= tot; ++i) {
		G[b[i].u].push_back(b[i].v);
		G[b[i].v].push_back(b[i].u);
	}
	for(int i = 1; i <= n; ++i) {
		if(!vis[i] && d[i] == 1) {
			if(!go(i)) return printf("No\n"), 0;
		}
	}
	printf("Yes\n");
	return 0;
}