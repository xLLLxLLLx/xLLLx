#include <bits/stdc++.h>
using namespace std;
const int N = 110;
struct data {
	int x, y;
} a[N];
vector<int> g[N];
int ans = 0, vis[N];
int d[N], res = 0, cnt = 0, b[N];

void dfs(int x, int fa) {
	if(d[x] == 1 && x != 1)
		b[++res] = x;
	for(int i = 0; i < g[x].size(); ++i) {
		int to = g[x][i];
		if(to == fa)
			continue;
		dfs(to, x);
	}
}

int n, k;
int c[N];

bool check() {
	int pos = c[1];
	for(int i = 2; i <= n; ++i) {
		int flg = 0;
		for(int j = 0; j < g[pos].size(); ++j) {
			if(g[pos][j] == c[i]) {
				flg = 1;
				pos = c[i];
				break;
			}
		}
		if(!flg) return false;
	}
	for(int i = 1; i <= n; ++i) {
		printf("%d ", c[i]);
	}
	puts("");
	return true;
}

void get(int dep, int lst) {
	// printf("qwq%d %d\n", dep, lst);
	if(dep > n) {
		ans++;
		return ;
	}
	for(int i = lst + 1; i <= cnt; ++i) {
		int x = a[i].x, y = a[i].y;
		vis[x]++, vis[y]++;
		if(vis[x] > 2 || vis[y] > 2) {
			vis[x]--, vis[y]--;
			continue;
		}
		get(dep + 1, i);
		vis[x]--, vis[y]--;
	}
}

int main() {
	freopen("polygon.in", "r", stdin);
	freopen("polygon.out", "w", stdout);
	scanf("%d%d", &n, &k);
	for(int i = 2, x; i <= n; ++i) {
		scanf("%d", &x);
		g[i].push_back(x);
		g[x].push_back(i);
		a[++cnt] = (data){i ,x};
		d[i]++, d[x]++;
	}
	dfs(1, 0);
	for(int i = 1; i <= res; ++i) 
		for(int j = i + 1; j <= res; ++j){
			int pos = min(abs(i - j), res - abs(i - j));
			if(pos <= k) {
				a[++cnt] = (data) {b[i], b[j]};
			}
	}
	// for(int i = 1; i <= n; ++i)
	// 	for(int j = 0; j < g[i].size(); ++j)
	// 		printf("%d %d\n", i, g[i][j]);
	get(1, 0);
	printf("%d\n", ans);
	return 0;
}