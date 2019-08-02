#include <bits/stdc++.h>
using namespace std;
const int N = 35;
int a[N][N], b[N][N], c[N][N], vis[N], mx[N];
char lx[N];
int n, m;

int zh(char ch) {
	if(ch == '0') return 0;
	else if(ch == '1') return 1;
	else return 2;
}

bool dfs(int x) {
	for(int i = 1; i <= m; ++i) {
		if(!b[x][i] || vis[i]) continue;
		vis[i] = 1;
		if(!mx[i] || dfs(mx[i])) {
			mx[i] = x;
			return true;
		}
	}
	return false;
}

bool check(int x, int y) {
	for(int i = 1; i <= n; ++i)
		if(a[i][x] == 2 || c[y][i] == 2 || a[i][x] == c[y][i]) continue;
		else return false;
	return true;
}

void add() {
	memset(b, 0, sizeof b);
	for(int i = 1; i <= m; ++i)
		for(int j = 1; j <= m; ++j) {
			if(check(i, j)) {
				// printf("qwq%d %d\n", i, j);
				b[i][j] = 1;
			}
		}
	// puts("end");
}

bool judge() {
	memset(mx, 0, sizeof mx);
	for(int i = 1; i <= m; ++i) {
		memset(vis, 0, sizeof vis);
		if(!dfs(i)) return false;
	}
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", lx + 1);
		for(int j = 1; j <= m; ++j) 
			a[i][j] = zh(lx[j]);
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%s", lx + 1);
		for(int j = 1; j <= n; ++j) 
			c[i][j] = zh(lx[j]);
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= m; ++j) {
			if(a[i][j] == 2) {
				a[i][j] = 0;
				add();
				if(!judge()) a[i][j] = 1;
			}
		}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) 
			printf("%d", a[i][j]);
		puts("");
	}
	return 0;
}