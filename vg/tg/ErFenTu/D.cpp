#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
const int N = 210;
vector <int> g;
int n, m;
int a[N][N], col[N], vis[N], mx[N], my[N], used[N];

bool dfsx(int x) {
	for(int i = 1; i <= n; ++i) {
		if(!a[x][i] || vis[i] || used[i]) continue;
		vis[i] = 1;
		if(!mx[i] || dfsx(mx[i])) {
			mx[i] = x;
			my[x] = i;
			return true;
		}
	}
	return false;
}

bool dfsy(int x) {
	for(int i = 1; i <= n; ++i) {
		if(!a[x][i] || vis[i] || used[i]) continue;
		vis[i] = 1;
		if(!my[i] || dfsy(my[i])) {
			my[i] = x;
			mx[x] = i;
			return true;
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) 
			scanf("%d", &col[i]);
		for(int i = 1, x, y; i <= m; ++i) {
			scanf("%d%d", &x, &y);
			x++, y++;
			if(col[x] != col[y]) a[x][y] = a[y][x] = 1;
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			if(col[i]) {
				memset(vis, 0, sizeof vis);
				ans += dfsx(i);
			}
		}
		printf("%d", ans);
		for(int i = 1; i <= n; ++i) {
			// for(int j = 1; j <= n; ++j) {
			// 	if(col[j]) {
			// 		printf("qwq%d %d\n", j, my[j]);
			// 	}
			// }
			// puts("end");
			memset(vis, 0, sizeof vis);
			if(col[i]) {
				if(my[i]) {
					int pos = my[i];
					mx[pos] = 0, my[i] = 0;
					used[i] = 1;
					if(dfsy(pos))
						used[i] = 0;
					else printf(" %d", i - 1);
				} 
			} else {
				if(mx[i]) {
					int pos = mx[i];
					my[pos] = 0, mx[i] = 0;
					used[i] = 1;
					if(dfsx(pos)) 
						used[i] = 0;
					else printf(" %d", i - 1);
				} 
			}
		}
		puts("");
		memset(a, 0, sizeof a);
		memset(mx, 0, sizeof mx);
		memset(my, 0, sizeof my);
		memset(used, 0, sizeof used);
	}
	return 0;
}