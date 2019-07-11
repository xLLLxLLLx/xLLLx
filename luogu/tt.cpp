#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10, M = 110;
struct data {
	int nt, to, w;
} a[N << 2];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int v[M][M], id[2][M][M], dis[N];
int head[N], cnt = 0;
typedef pair<int, int> P;
priority_queue<P, vector<P>, greater<P> > q;

void add(int x, int y, int w) {
	a[++cnt].to = y;
	a[cnt].w = w;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dijstra() {
	memset(dis, 0x3f, sizeof dis);
	dis[id[v[1][1]][1][1]] = 0;
	q.push(P(0, id[v[1][1]][1][1]));
	while(!q.empty()) {
		P p = q.top(); q.pop();
		int v = p.second;
		if(dis[v] < p.first) continue;
		for(int i = head[v]; i; i = a[i].nt) {
			int to = a[i].to;
			if(dis[to] > dis[v] + a[i].w) {
				dis[to] = dis[v] + a[i].w;
				q.push(P(dis[to], to));
			}
		}
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	memset(v, -1, sizeof v);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		scanf("%d", &v[x][y]);
	}
	int res = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			if(v[i][j] == -1) {
				id[0][i][j] = ++res;
				id[1][i][j] = ++res;
			} else {
				id[v[i][j]][i][j] = ++res;
			}
		}
	for(int x = 1; x <= n; ++x)
		for(int y = 1; y <= n; ++y) {
			for(int o = 0; o < 4; ++o) {
				int xx = x + dx[o], yy = y + dy[o];
				if(xx < 1 || xx > n || yy < 1 || yy > n) continue;
				if(v[xx][yy] == -1) {
					if(v[x][y] == -1) continue;
					else {
						for(int i = 0; i < 2; ++i) {
							add(id[v[x][y]][x][y], id[i][xx][yy], 2 + (i != v[x][y]));
						}
					}
				} else {
					if(v[x][y] == -1) {
						for(int i = 0; i < 2; ++i) {
							add(id[i][x][y], id[v[xx][yy]][xx][yy], (i != v[xx][yy]));
						}
					} else {
						add(id[v[x][y]][x][y], id[v[xx][yy]][xx][yy], v[x][y] != v[xx][yy]);
					}
				}
			}
		}
	dijstra();
	int maxn = 1e9;
	for(int i = 0; i < 2; ++i) {
		if(id[i][n][n]) {
			maxn = min(maxn, dis[id[i][n][n]]);
		}
	}
	if(maxn == 1e9) printf("-1\n");
	else printf("%d\n", maxn);
	return 0;
} 