#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int N = 2e5 + 10, M = 4e5 + 10, LOG = 21;
struct data {
	int nt, to, w;
} a[M << 1], b[M];
int n, m;
int head[N], f[N], cnt = 0;

void add(int x, int y, int w) {
	a[++cnt].to = y;
	a[cnt].w = w;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int dis[N];
typedef pair<int, int> P;
priority_queue<P, vector<P>, greater<P> > q;

void dij() {
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0;
	q.push(P(0, 1));
	while(!q.empty()) {
		P h = q.top(); q.pop();
		int u = h.second, w = h.first;
		if(dis[u] < w) continue;
		for(int i = head[u]; i; i = a[i].nt) {
			int to = a[i].to;
			if(dis[to] > dis[u] + a[i].w) {
				dis[to] = dis[u] + a[i].w;
				q.push(P(dis[to], to));
			}
		}
	}
}

bool cmp(data A, data B) {
	return A.w > B.w;
}

int find(int k) {
	return f[k] == k ? f[k] : f[k] = find(f[k]);
}

vector<int> g[N];
int fa[N][LOG + 1], val[N], mn[N], tot;

void kruskal() {
	tot = n;
	sort(b + 1, b + 1 + m, cmp);
	for(int i = 1; i <= n * 2; ++i)
		f[i] = i;
	int now = 0;
	for(int i = 1; i <= m; ++i) {
		if(now == n - 1) return;
		int x = b[i].nt, y = b[i].to;
		int fx = find(x), fy = find(y);
		if(fx != fy) {
			++tot;
			val[tot] = b[i].w;
			g[tot].push_back(fx), g[tot].push_back(fy);
			f[fx] = f[fy] = tot;
			++now;
		}
	}
}

void dfs(int u) {
	// printf("dfs%d\n", u);
	if(u <= n) mn[u] = dis[u];
	for(int i = 0; i < g[u].size(); ++i) {
		int to = g[u][i];
		fa[to][0] = u;
		dfs(to);
		mn[u] = min(mn[u], mn[to]);
	}
}

void init() {
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= tot; ++i)
			fa[i][j] = fa[fa[i][j - 1]][j - 1];
}

int main() {
	freopen("return.in", "r", stdin);
	freopen("return.out", "w", stdout);
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d%d", &n, &m);
		for(int i = 1, x, y, d, h; i <= m; ++i) {
			scanf("%d%d%d%d", &x, &y, &d, &h);
			add(x, y, d), add(y, x, d);
			b[i].nt = x, b[i].to = y, b[i].w = h;
		}
		dij(), kruskal();
		memset(mn, 0x3f, sizeof mn);
		dfs(tot), init();
		// for(int i = 1; i <= tot; ++i)
		// 	for(int j = 0; j <= LOG; ++j) {
		// 		if(fa[i][j]) 
		// 			printf("fa[%d][%d]=%d\n", i, j, fa[i][j]);
		// 	}
		// for(int i = 1; i <= tot; ++i)
		// 	printf("mn[%d]=%d dis=%d\n", i, mn[i], dis[i]);
		int Q, k, s, ans = 0;
		scanf("%d%d%d", &Q, &k, &s);
		for(int i = 1, x, y; i <= Q; ++i) {
			scanf("%d%d", &x, &y);
			x = (x + k * ans - 1) % n + 1;
			y = (y + k * ans) % (s + 1);
			// printf("%d %d\n", x, y);
			for(int j = LOG; j >= 0; --j) {
				if(fa[x][j]) {
					if(val[fa[x][j]] > y)
						x = fa[x][j];
				}
			}
			// printf("qwq%d %d\n", x, tot);
			ans = mn[x];
			printf("%d\n", ans);
		}
		for(int i = 1; i <= tot; ++i)
			for(int j = 0; j <= LOG; ++j)
				fa[i][j] = 0;
		for(int i = 1; i <= tot; ++i)
			g[i].clear();
		cnt = 0;
		for(int i = 1; i <= n; ++i)
			head[i] = 0;
	}
	return 0;
}