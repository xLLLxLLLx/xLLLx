#include <bits/stdc++.h>
using namespace std;
const int N = 510;
struct data {
	int nt, to;
} a[N * 110];
int head[N], vis[N], mx[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
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
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m;
		scanf("%d%d", &n, &m);
		cnt = 0;
		for(int i = 1; i <= n; ++i) {
			head[i] = 0;
		}
		for(int i = 1; i <= m; ++i) {
			mx[i] = 0;
		}
		for(int i = 1, num; i <= n; ++i) {
			scanf("%d", &num);
			for(int j = 1, x; j <= num; ++j) {
				scanf("%d", &x);
				add(i, x);
			}
		}
		int ans = 0;
		for(int i = 1; i <= n; ++i) {
			memset(vis, 0, sizeof vis);
			ans += dfs(i);
		}
		if(ans == n) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}