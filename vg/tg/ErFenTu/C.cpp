#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int n, m, num;
vector<int> c, r;
int a[N][N], vis[N], vx[N], mx[N], my[N];

bool dfs(int x) {
	vx[x] = 1;
	for(int i = 1; i <= m; ++i) {
		if(!a[x][i] || vis[i]) {
			continue;
		}
		vis[i] = 1;
		if(!mx[i] || dfs(mx[i])) {
			mx[i] = x;
			my[x] = i;
			return true;
		}
	}
	return false;
}

int main() {
	while(scanf("%d%d%d", &n, &m, &num) == 3 && (n || m || num)) {
		memset(a, 0, sizeof a);
		for(int i = 1, x, y; i <= num; ++i) {
			scanf("%d%d", &x, &y);
			a[x][y] = 1;
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			memset(vis, 0, sizeof vis);
			ans += dfs(i);
		}
		printf("%d", ans);
		memset(vx, 0, sizeof vx);
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= n; ++i)
			if(!my[i]) 
				dfs(i);
		for(int i = 1; i <= n; ++i)
			if(!vx[i])
				printf(" r%d", i);
		for(int i = 1; i <= m; ++i) 
			if(vis[i])
				printf(" c%d", i);
		puts("");

		for(int i = 1; i <= n; ++i)
			vx[i] = 0, my[i] = 0;
		for(int i = 1; i <= m; ++i)
			vis[i] = 0, mx[i] = 0;
	}
	return 0;
}