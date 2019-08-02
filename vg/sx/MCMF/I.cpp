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
int cnt = -1, tot = 0;
int head[N], dis[N], pa[N];
bool vis[N];

void init() {
	cnt = -1, tot = 0;
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
	// for(int i = S; i <= T; ++i) {
	// 	printf("%d %d\n", i, dis[i]);
	// }
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
		d[++tot] = (node){minflow, dis[T]};
		mincost += dis[T] * minflow;
	}
	return mincost;
}

int k;

bool check(int t) {
	ll ans = 0;
	for(int i = 1; i <= tot; ++i) {
		if(d[i].cost > t) continue;
		ans += 1ll * (t - d[i].cost + 1) * d[i].flow;
	}
	return ans >= k;
}

int main() {
	int n, m;
	while(scanf("%d%d%d", &n, &m, &k) == 3) {
		init();
		for(int i = 1; i <= m; ++i) {
			int x, y, z;
			scanf("%d%d%d", &x, &y, &z);
			x++, y++;
			add(x, y, z, 1);
		}
		int S = 1, T = n;
		MCMF(S, T, n);
		int l = 0, r = k + m, ans = -1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			if(check(mid)) ans = mid, r = mid - 1;
			else l = mid + 1;
		}
		if(ans == -1) printf("No solution\n");
			else printf("%d\n", ans);
	}
	return 0;
}