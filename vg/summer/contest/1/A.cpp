#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 110;
const int inf = 1e9;
struct data {
	int nt, to;
} a[N << 1];
vector<int> g;
queue<int> q;
int col[N], d[N], dis[M];
int head[N], vis[M], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int main() {
	int n, m, s, k;
	cin >> n >> m >> s >> k;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &col[i]);
	}
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	for(int i = 1; i <= n; ++i) d[i] = inf;
	for(int i = 1; i <= n; ++i) {
		memset(vis, 0, sizeof vis);
		vis[col[i]] = 1;
		d[i] = 0, g.push_back(i);
		int res = k - 1, ans = 0;
		q.push(i);
		while(!q.empty()) {
			if(!res) break;
			int h = q.front(); q.pop();
			// printf("qwqw%d %d\n", h, d[h]);
			for(int i = head[h]; i; i = a[i].nt) {
				int to = a[i].to;
				if(d[to] > d[h] + 1) {
					q.push(to), g.push_back(to);
					d[to] = d[h] + 1;
					if(!vis[col[to]]) {
						// printf("???\n");
						ans += d[to];
						vis[col[to]] = 1;
						res--;
					}
				}
				if(!res) break;
			}
		}
		int len = g.size();
		while(!q.empty()) {
			q.pop();
		}
		for(int i = 0; i < len; ++i) {
			d[g[i]] = inf;
		}
		g.clear();
		printf("%d ", ans);
	}
	return 0;
}