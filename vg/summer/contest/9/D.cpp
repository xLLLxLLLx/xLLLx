#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;
struct data {
	int x, y;
} a[N << 1];
queue<int> Q;
vector<int> g[N];
int q[N], d[N], vis[N], dis[N], fr[N];

void read(int &x) {
	char ch = getchar(); x = 0;
	for(;ch < '0' || ch > '9'; ch = getchar()) ;
	for(;ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

void print(int x) {
	if(fr[x]) print(fr[x]);
	printf("%d ", x);
}

int main() {
	int n, m, cnt = 0;
	read(n), read(m);
	for(int i = 1, x, y; i <= m; ++i) {
		read(x), read(y);
		g[x].push_back(y), g[y].push_back(x);
		d[x]++, d[y]++;
		if(x == 1 || y == 1) {
			continue;
		}
		a[++cnt].x = x, a[cnt].y = y;
		a[++cnt].x = y, a[cnt].y = x;
	}

	//case 1
	memset(dis, 0x3f, sizeof dis);
	dis[1] = 0, Q.push(1);
	while(!Q.empty()) {
		int h = Q.front(); Q.pop();
		if(dis[h] >= 4) {
			break;
		}
		int len = g[h].size();
		for(int i = 0; i < len; ++i) {
			int to = g[h][i];
			if(dis[to] > dis[h] + 1) {
				dis[to] = dis[h] + 1;
				fr[to] = h;
				Q.push(to);
			}
		}
	}
	if(dis[n] <= 4) {
		printf("%d\n", dis[n]), print(n);
		return 0;
	}

	//case2
	int len = g[1].size();
	for(int i = 0; i < len; ++i) {
		vis[g[1][i]] = 1;
	}
	for(int i = 1; i <= cnt; ++i) {
		if(vis[a[i].x] && !vis[a[i].y]) {
			return printf("4\n1 %d %d 1 %d\n", a[i].x, a[i].y, n), 0;
		}
	}

	//case3
	memset(vis, 0, sizeof vis);
	for(int i = 0; i < len; ++i) {
		if(!vis[g[1][i]]) {
			int x = g[1][i];
			vis[x] = 1;
			int vertex = 0, edge = 0, l = 1, r = 1;
			q[1] = x;
			while(l <= r) {
				int now = q[l];
				vertex++, edge += d[now] - 1;
				int tot = g[now].size();
				for(int j = 0; j < tot; ++j) {
					int to = g[now][j];
					if(vis[to] || to == 1) {
						continue;
					}
					vis[to] = 1;
					q[++r] = to;
				}
				l++;
			}
			if(r < 3 || 1ll * vertex * (vertex - 1) == edge) continue;
			for(int j = 1; j <= r; ++j) {
				if(d[q[j]] >= vertex) continue;
				memset(vis, 0, sizeof vis);
				int now = q[j], ed = g[now].size();
				for(int k = 0; k < ed; ++k) {
					vis[g[now][k]] = 1;
				}
				for(int k = 0; k < ed; ++k) {
					if(g[now][k] == 1) continue;
					int v = g[now][k], pos = g[v].size();
					for(int t = 0; t < pos; ++t) {
						if(!vis[g[v][t]] && g[v][t] != now) {
							return printf("5\n1 %d %d %d %d %d\n", now, v, g[v][t], now, n) , 0;
						}
					}
				}
			}
		}
	}
	puts("-1");
	return 0;
}