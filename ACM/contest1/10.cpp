#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3010;
struct data {
	int nt, to, w;
} a[N << 1];
int cnt = 0;
int head[N];
ll dis[N], v[N];
typedef pair<ll, int> P;
priority_queue<P, vector<P>, greater<P> > q;

void add(int x, int y, int w) {
	a[++cnt].to = y;
	a[cnt].w = w;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int n, m, k;

void go(ll w) {
	for(int i = 1; i <= n; ++i) {
		dis[i] = 1e13;
	}
	dis[1] = 0;
	q.push(P(0, 1));
	while(!q.empty()) {
		P p = q.top(); q.pop();
		int v = p.second;
		if(dis[v] < p.first) continue;
		for(int i = head[v]; i; i = a[i].nt) {
			int to = a[i].to;
			ll now = max(a[i].w - w, 0ll);
			if(dis[to] > dis[v] + now) {
				dis[to] = dis[v] + now;
				q.push(P(dis[to], to));
			}
		}
	}
}

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for(int i = 1; i <= m; ++i) {
		int x, y, w;
		scanf("%d%d%d", &x, &y, &w);
		add(x, y, w);
		add(y, x, w);
		v[i] = w;
	}
	ll ans = 1e18;
	v[++m] = 0;
	for(int i = 1; i <= m; ++i) {
		go(v[i]);
		// printf("%lld %lld\n", v[i], dis[n]);
		ans = min(ans, dis[n] + v[i] * k);
	}
	printf("%lld\n", ans);
	return 0;
}