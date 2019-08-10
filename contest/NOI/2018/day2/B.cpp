#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e4 + 10, LOG = 17;
struct data {
	int nt, to, w;
} a[N << 1];
struct node {
	int x, y;
	ll w;
} b[N];
ll qz[N];
int n, m, cnt = 0;
int head[N], L[N], val[N], g[N][LOG + 1], dep[N];

void add(int x, int y, int w) {
	a[++cnt].to = y;
	a[cnt].w = w;
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
		val[to] = a[i].w;
		dfs(to, u);
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
		if(dep[g[B][i]] >= dep[A])
			B = g[B][i];
	if(A == B)
		return A;
	for(int i = LOG; i >= 0; --i) {
		if(g[A][i] != g[B][i])
			A = g[A][i], B = g[B][i];
	}
	return g[A][0];
}

int get(int x) {
	for(int i = LOG; i >= 0; --i) {
		if(dep[g[x][i]] > 1)
			x = g[x][i];
	}
	return x;
}

int vis[N];

void sub(int u, int fa) {
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa)
			continue;
		sub(to, u);
		vis[u] += vis[to];
	}
}

int main() {
	freopen("center.in", "r", stdin);
	freopen("center.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d", &n);
		for(int i = 1, x, y, z; i < n; ++i) {
			scanf("%d%d%d", &x, &y, &z);
			add(x, y, z);
		}
		dfs(1, 0), yyqx();
		scanf("%d", &m);
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d%lld", &b[i].x, &b[i].y, &b[i].w);
			L[i] = GetLCA(b[i].x, b[i].y);
		}
		if(n <= 1000) {
			ll maxn = -1e17;
			for(int i = 1; i <= m; ++i)
				for(int j = i + 1; j <= m; ++j) {
					fill(vis + 1, vis + 1 + n, 0);
					vis[b[i].x]++, vis[b[i].y]++;
					vis[L[i]] -= 2;
					vis[b[j].x]++, vis[b[j].y]++;
					vis[L[j]] -= 2;
					sub(1, 0);
					ll pos = -(b[i].w + b[j].w);
					int flg = 0;
					for(int k = 1; k <= n; ++k) {
						if(vis[k] >= 2) {
							flg = 1;
						}
						if(vis[k]) {
							pos += val[k];
						}
					}
					if(!flg) continue;
					maxn = max(maxn, pos);
				}
			if(maxn == -1e17) {
				puts("F");
			} else {
				printf("%lld\n", maxn);
			}
		}
		cnt = 0;
		fill(head + 1, head + 1 + n, 0);
	}
	return 0;
}