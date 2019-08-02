#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
const int N = 1e4 + 10, M = 1e4 + 10, inf = 1e9;
struct Edge {
	int u, v, cap, cost;
	int nt;
} a[M << 2];
int dx[2] = {1, 0};
int dy[2] = {0, 1};
int cnt = -1, totflow = 0;
int head[N], dis[N], pa[N];
bool vis[N];

void init() {
	cnt = -1;
	memset(head, -1, sizeof head);
}

void add(int u, int v, int cap, int cost) {
	a[++cnt] = (Edge){u, v, cap, cost, head[u]};
	head[u] = cnt;
	a[++cnt] = (Edge){v, u, 0, -cost, head[v]};
	head[v] = cnt;
}

bool spfa(int S, int T, int n) {
	queue<int> q;
	memset(vis, false, sizeof vis);
	memset(pa, -1, sizeof pa);
	for(int i = 0; i <= n; ++i) dis[i] = inf;
	vis[S] = 1, dis[S] = 0;
	q.push(S);
	while(!q.empty()) {
		int u = q.front(); q.pop();
		// printf("%d\n", u);
		vis[u] = 0;
		for(int i = head[u]; ~i; i = a[i].nt) {
			int v = a[i].v;
			if(a[i].cap && dis[v] > dis[u] + a[i].cost) {
				dis[v] = dis[u] + a[i].cost;
				pa[v] = i;
				if(!vis[v]) {
					q.push(v);
				}
				vis[v] = 1;
			}
		}	
	}
	return dis[T] != inf;
}

int MCMF(int S, int T, int n) {
	int flow = 0;
	int mincost = 0;
	for(; spfa(S, T, n); ) {
		int minflow = inf + 1;
		for(int i = pa[T]; ~i; i = pa[a[i].u]) {
			minflow = min(minflow, a[i].cap);
		}
		flow += minflow;
		for(int i = pa[T]; ~i; i = pa[a[i].u]) {
			a[i].cap -= minflow;
			a[i ^ 1].cap += minflow;
		}
		// printf("%d %d\n", minflow, dis[T]);
		printf("%d %d\n", minflow, dis[T]);
		mincost += dis[T] * minflow;
	}
	totflow = flow;
	return mincost;
}

int val[N][N];

int js(int x, int y, int n) {
	return (x - 1) * n + y;
}

int main() {
	int n, k;
	while(scanf("%d%d", &n, &k) == 2) {
		init();
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				scanf("%d", &val[i][j]);
			}
		}
		int NE = 2 * n * n + 2;
		int S = 0, T = 2 * n * n + 1;
		add(S, 1, k, 0);
		for(int i = 1; i <= n; ++i) {
			for(int j = 1; j <= n; ++j) {
				add(js(i, j, n), js(i, j, n) + n * n, 1, -val[i][j]);
				add(js(i, j, n), js(i, j, n) + n * n, inf, 0);
				for(int k = 0; k < 2; ++k) {
					int xx = i + dx[k], yy = j + dy[k];
					if(xx <= 0 || yy <= 0 || xx > n || yy > n) continue;
					add(js(i, j, n) + n * n, js(xx, yy, n), inf, 0);
				}
			}
		}
		add(T - 1, T, k, 0);
		printf("%d\n", -MCMF(S, T, NE));
	}
	return 0;
}