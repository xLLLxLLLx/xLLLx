#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 3010, M = 6e6 + 10;
struct data {
	int nt, to;
}a[M << 1];
char lx[5];
int n, m;
int cnt = 0, res = 0;
int head[N], vis[N], c[N], col[N];

void add(int x, int y) {
	// printf("%d %d\n",x,y);
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void equal(int x, int y) {
	add(x + n, y + n);
	add(y, x);
	add(x, y);
	add(y + n, x + n);
}

void dfs(int x, int y) {
	vis[x] = 1;
	col[x] = y;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(!vis[to]) {
			dfs(to, y);
		}
	}
	if(!y) {
		c[++c[0]] = x;
	}
}

int main() {
	while(scanf("%d%d", &n, &m) == 2) {
		memset(head, 0, sizeof head);
		memset(vis, 0, sizeof vis);
		memset(col, 0, sizeof col);
		cnt = 0, res = 0, c[0] = 0;
		for(int i = 1, x, y, z; i <= m; ++i) {
			scanf("%d%d%d%s", &x, &y, &z, lx);
			x++, y++;
			if(lx[0] == 'A') {
				if(z) {
					add(x + n, y);
					add(y + n, x);
					equal(x, y);
				} else {
					add(x, y + n);
					add(y, x + n);
				}
			} else if(lx[0] == 'O') {
				if(z) {
					add(x + n, y);
					add(y + n, x);
				} else {
					add(x, y + n);
					add(y, x + n);
					equal(x, y);
				}
			} else if(lx[0] == 'X') {
				if(z) {
					add(x, y + n);
					add(y, x + n);
					add(x + n, y);
					add(y + n, x);
				} else {
					equal(x, y);
				}
			}
		}
		for(int i = 1; i <= 2 * n; ++i) {
			if(!vis[i]) {
				dfs(i, 0);
			}
		}
		memset(vis, 0, sizeof vis);
		for(int i = 1; i <= c[0]; ++i) {
			if(!vis[c[i]]) {
				dfs(c[i], ++res);
			}
		}
		for(int i = 1; i <= n; ++i) {
			if(col[i] == col[i + n]) {
				return printf("NO\n"), 0;
			}
		}
		printf("YES\n");
	}
	return 0;
}