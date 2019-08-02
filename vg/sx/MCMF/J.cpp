#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define ll long long
using namespace std;
const int N = 2510, M = 5010, inf = 1e9;
struct Edge {
	int u, v, cap, cost;
	int nt;
} a[M << 2];
struct node {
	int flow, cost;
} d[M];
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
	puts("!!!!");
	for(int i = S; i <= T; ++i) {
		printf("%d %d\n", i, dis[i]);
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
		printf("%d %d\n", minflow, dis[T]);
		mincost += dis[T] * minflow;
	}
	totflow = flow;
	return mincost;
}

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) == 2) {
		init();
		int S = 0, T = 2 * n + 1;
		for(int i = 1; i <= n; ++i) {
			add(S, i, inf, 0);
			add(i + n, T, 1, 0);
			add(i, i + n, inf, 0);
		}
		for(int i = 1; i <= m; ++i) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			add(x + n, y, 1, -z);
		}
		int pos = MCMF(S, T, T);
		if(totflow != n) {
			puts("-1");
		} else {
			printf("%d\n", -pos);
		}
	}
	return 0;
}