#include <bits/stdc++.h>
using namespace std;
const int N = 510, M = 250010;
int w[N], l[N], h[N];
struct data {
	int nt, to;
} a[M];
int head[N], vis[N << 1], mx[N << 1], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void init() {
	cnt = 0;
	memset(head, 0, sizeof head);
	memset(mx, 0, sizeof mx);
}

bool check(int x, int y) {
	return w[x] < w[y] && l[x] < l[y] && h[x] < h[y];
}

bool dfs(int x) {
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(vis[to]) continue;
		vis[to] = 1;
		if(!mx[to] || dfs(mx[to])) {
			mx[to] = x;
			return true;
		}
	}
	return false;
}

int main() {
	int n;
	while(scanf("%d", &n) == 1 && n) {
		init();
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d%d", &w[i], &l[i], &h[i]);
		}
		for(int i = 1; i <= n; ++i) 
			for(int j = 1; j <= n; ++j) {
				if(check(i, j)) {
					add(j, i + n);
				}
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			memset(vis, 0, sizeof vis);
			ans += dfs(i);
		}
		printf("%d\n", n - ans);
	}	
	return 0;	
}