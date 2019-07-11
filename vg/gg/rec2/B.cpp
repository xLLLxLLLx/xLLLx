#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 510;
ll dis[N][N];
int head[N], a[N][N], cnt[N], d[N][N];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	memset(dis, 0x3f, sizeof dis);
	for(int i = 1; i <= n; ++i) dis[i][i] = 0;
	for(int i = 1, x, y, w; i <= m; ++i) {
		scanf("%d%d%d", &x, &y, &w);
		a[x][y] = a[y][x] = w;
		dis[x][y] = dis[y][x] = w;
	}
	for(int k = 1; k <= n; ++k)
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= n; ++j) {
				dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
			}
	for(int i = 1; i <= n; ++i){
		memset(cnt, 0, sizeof cnt);
		for(int j = 1; j <= n; ++j) {
			for(int k = 1; k <= n; ++k) {
				if(a[k][j]) {
					if(dis[i][k] + a[k][j] == dis[i][j]) {
						cnt[j]++;
					}
				}
			}
			for(int k = 1; k <= n; ++k) {
				if(dis[i][k] == dis[i][j] + dis[j][k]) {
					d[i][k] += cnt[j];
				}
			}
		}
	}
	for(int i = 1; i <= n; ++i) 
		for(int j = i + 1; j <= n; ++j) {
			printf("%d ", d[i][j]);
		}
	return 0;
}