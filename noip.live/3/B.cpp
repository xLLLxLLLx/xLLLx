#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int n, m, flg = 0;
char lx[N];
vector<int> g[N];
int a[N][N], b[N][N], d[N][N], c[N][N], vis[N];

int zh(char ch) {
	if(ch == '0') return 0;
	if(ch == '1') return 1;
	else return 2;
}

bool check() {
	if(!flg) return 1;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			if(b[i][j] > d[i][j]) return true;
			else if(b[i][j] < d[i][j]) return false;
		}
	return false;
}

void change() {
	if(check()) {
		for(int i = 1; i <= n; ++i)
			for(int j = 1; j <= m; ++j) {
				b[i][j] = d[i][j];
			}
	}
	flg = 1;
}

bool check(int x, int y) {
	for(int i = 1; i <= n; ++i)
		if(a[i][x] == 2 || c[y][i] == 2 || a[i][x] == c[y][i]) continue;
		else return false;
	return true;
}

int get(int x, int y) {
	if(x == 2 && y == 2) return 0;
	if(!x || !y) return 0;
	if(x == 2) return y;
	if(y == 2) return x;
	return x;
}

void dfs(int dep) {
	if(dep == m + 1) {
		change();
		return ;
	}
	for(int i = 0; i < g[dep].size(); ++i) {
		int now = g[dep][i];
		if(vis[now]) continue;
		vis[now] = 1;
		for(int j = 1; j <= n; ++j) {
			d[j][dep] = get(a[j][dep], c[now][j]);
		}
		dfs(dep + 1);
		vis[now] = 0;
	}
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", lx + 1);
		for(int j = 1; j <= m; ++j) {
			a[i][j] = zh(lx[j]);
		}
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%s", lx + 1);
		for(int j = 1; j <= n; ++j)
			c[i][j] = zh(lx[j]);
	}
	
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= m; ++j) {
			if(check(i, j)) {
				g[i].push_back(j);
			}
		}

	dfs(1);

	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j)
			printf("%d", b[i][j]);
		puts("");
	}
	return 0;
}