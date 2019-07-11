#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int a[N][N];
int dp[N][N][2][2], vis[N][N][2][2];
struct data {
	int x, y, z, w;
};
queue<data> q;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	memset(a, -1, sizeof a);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		scanf("%d", &a[x][y]);
	}
	memset(dp, 0x3f, sizeof dp);
	vis[1][1][a[1][1]][0] = 1;
	dp[1][1][a[1][1]][0] = 0;
	q.push((data){1, 1, a[1][1], 0});
	while(!q.empty()) {
		data h = q.front(); q.pop();
		vis[h.x][h.y][h.z][h.w] = 0;
		// printf("%d %d %d %d\n", h.x, h.y, h.z, h.w);
		for(int i = 0; i < 4; ++i) {
			int xx = h.x + dx[i], yy = h.y + dy[i];
			if(xx < 1 || xx > n || yy < 1 || yy > n) continue;
			if(a[xx][yy] != -1) {
				int pos = dp[h.x][h.y][h.z][h.w] + (h.z != a[xx][yy]);
				if(dp[xx][yy][a[xx][yy]][0] > pos) {
					if(!vis[xx][yy][a[xx][yy]][0]) {
						q.push((data){xx, yy, a[xx][yy], 0});
						vis[xx][yy][a[xx][yy]][0] = 1;
					}
					dp[xx][yy][a[xx][yy]][0] = pos;
				}
			} else {
				if(h.w) continue;
				int pos = dp[h.x][h.y][h.z][h.w] + 2;
				if(dp[xx][yy][h.z][1] > pos) {
					if(!vis[xx][yy][h.z][1]) {
						vis[xx][yy][h.z][1] = 1;
						q.push((data){xx, yy, h.z, 1});
					}
					dp[xx][yy][h.z][1] = pos;
				} else if(dp[xx][yy][1 - h.z][1] > pos + 1) {
					if(!vis[xx][yy][1 - h.z][1]) {
						vis[xx][yy][1 - h.z][1] = 1;
						q.push((data){xx, yy, 1 - h.z, 1});
					}
					dp[xx][yy][1 - h.z][1] = pos + 1;
				}
			}
		}
	}
	int maxn = 1e9;
	for(int i = 0; i < 2; ++i)
	 for(int j = 0; j < 2; ++j){
		maxn = min(maxn, dp[n][n][i][j]);
	}
	if(maxn == 1e9) printf("-1\n");
	else printf("%d\n", maxn);
	return 0;
}