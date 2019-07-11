#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N = 2510, M = 5e5 + 10;
struct data {
	int nt, to;
}a[M << 1];
int n, m;
int cnt = 0, res = 0;
int b[N][2];
int head[N], col[N], vis[N], c[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void Add(int x, int y) {
	add(x, y + m);
	add(y, x + m);
	add(x + m, y);
	add(y + m, x);
}

bool check(int x, int y) {
	return 1ll * (b[x][0] - b[y][0]) * (b[x][1] - b[y][0]) * 
					(b[x][0] - b[y][1]) * (b[x][1] - b[y][1]) < 0ll;
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
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &b[i][0], &b[i][1]);
		b[i][0] ++, b[i][1] ++;
		if(b[i][0] > b[i][1]) {
			swap(b[i][0], b[i][1]);
		}
	}
	for(int i = 1; i <= m; ++i) {
		for(int j = i+1; j <= m; ++j) {
			if(check(i, j)) {
				// printf("%d %d\n", i, j);
				Add(i, j);
			}
		}
	}
	for(int i = 1; i <= 2 * m; ++i) {
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
	for(int i = 1; i <= m; ++i) {
		if(col[i] == col[i + m]) {
			return printf("the evil panda is lying again\n"), 0;
		}
	}
	printf("panda is telling the truth...\n");
	return 0;
}