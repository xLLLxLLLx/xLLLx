#include <bits/stdc++.h>
using namespace std;
const int E = 3610, N = 65, M = 1e5 + 10;
struct data {
	int nt, to;
} a[E];
vector <int> g;
int head[N], my[N];
int vis[M], mx[M], s[M];
int cnt = 0, now = 0;

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
			my[x] = to;
			s[++now] = to;
			return true;
		}
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		for(int i = 1, l, r; i <= n; ++i) {
			scanf("%d%d", &l, &r);
			r = min(r, l + n - 1);
			for(int j = l; j <= r; ++j)
				add(i, j);
		}
		g.clear();
		for(int i = n; i >= 1; --i) {
			if(dfs(i)) g.push_back(i);
			for(int j = 1; j <= now; ++j)
				vis[s[j]] = 0;
		}
		printf("%d\n", (int)g.size());
		for(int i = g.size() - 1; i >= 0; --i) {
			printf("%d%c", g[i], i ? ' ' : '\n');
		}
		for(int i = 1; i <= n; ++i) {
			if(my[i]) mx[my[i]] = 0, my[i] = 0;
			head[i] = 0;
		}
		cnt = now = 0;
	}
	return 0;
}