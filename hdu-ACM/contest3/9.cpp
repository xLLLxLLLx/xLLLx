#pragma GCC optimize(2)
#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;
const int INF = 0x7fffffff;
const int N = 4010, M = 3e6 + 10;
struct data {
	int to, cap, cost;
	int rev;
};
vector <data> g[N];
int dis[N], h[N], preve[N], prevv[N];

typedef pair<int, int> P;
priority_queue <P, vector<P>, greater<P> > q;

void read(int &x) {
	char ch = getchar(); x = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) ;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

void init(int n) {
	for(int i = 0; i <= n; ++i)
		g[i].clear(), h[i] = 0;
}

void add(int u, int v, int cap, int cost) {
	g[u].push_back((data){v, cap, cost, (int)g[v].size()});
	g[v].push_back((data){u, 0, -cost, (int)g[u].size() - 1});
}

bool dij(int S, int T, int V) {
	fill(dis, dis + 1 + V, INF);
	dis[S] = 0; q.push(P(0, S));
	while (!q.empty()) {
		P now = q.top(); q.pop();
		int u = now.second;
		if (dis[u] < now.first) continue;
		for (int i = 0; i < g[u].size(); ++i) {
			data &e = g[u][i];
			int v = e.to;
			if (e.cap > 0 && dis[v] > dis[u] + e.cost + h[u] - h[v]) {
				dis[v] = dis[u] + e.cost + h[u] - h[v];
				prevv[v] = u;
				preve[v] = i;
				q.push(P(dis[v], v));
			}
		}
	}
	return dis[T] != INF;
}

int MCMF(int S, int T, int f) {
	int mincost = 0;
	for(; f > 0 && dij(S, T, T); ) {
		int minflow = f;
		for(int i = S; i <= T; ++i)
			h[i] += dis[i];
		for(int v = T; v != S; v = prevv[v]) {
			minflow = min(minflow, g[prevv[v]][preve[v]].cap);
		}
		for(int v = T; v != S; v = prevv[v]) {
			data &e = g[prevv[v]][preve[v]];
			e.cap -= minflow;
			g[v][e.rev].cap += minflow;
		}
		f -= minflow;
		mincost += h[T] * minflow;
	}
	return mincost;
}

int s[N];

int main() {
	int cas;
	scanf("%d", &cas);
	for(int o = 1; o <= cas; ++o) {
		int n, k;
		read(n), read(k);
		int s1 = 0, s2 = 2 * n + 1, t = 2 * n + 2;
		init(t);
		add(s1, s2, k, 0);
		for (int i = 1; i <= n; ++i) {
			read(s[i]);
			add(i, i + n, 1, -s[i]);
		}
		for (int i = 1; i <= n; ++i)
			for (int j = i + 1; j <= n; ++j) {
				if (s[i] <= s[j]) add(i + n, j, 1, 0);
			}
		for (int i = 1; i <= n; ++i) {
			add(s2, i, 1, 0);
			add(i + n, t, 1, 0);
		}
		printf("%d\n", -MCMF(s1, t, k));
	}
	return 0;
}