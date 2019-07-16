#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct data {
	int nt, to;
} a[N];
vector<int> g[N];
struct node {
	int x, id;
};
queue<node> q;
int head[N], dfn[N], vis[N], low[N], st[N], top = 0, res = 0, cnt = 0, maxn = 0;
int fr[N][2], f[N][2], d[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void print(int x, int id) {
	printf("%d ", x);
	if(fr[x][id]) {
		print(fr[x][id], id ^ 1);
	}
}

void dfs(int x) {
	vis[x] = 1, st[++top] = x;
	dfn[x] = low[x] = ++res;
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(!dfn[to]) {
			dfs(to);
			low[x] = min(low[x], low[to]);
		} else if(vis[to]) {
			low[x] = min(low[x], dfn[to]);
		}
	}
	if(dfn[x] == low[x]) {
		int pos = 0;
		while(st[top] != x) {
			pos++;
			vis[st[top--]] = 0;
		}
		pos++, vis[st[top--]] = 0;
		maxn = max(maxn, pos);
	}
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &d[i]);
		for(int j = 1, x; j <= d[i]; ++j) {
			scanf("%d", &x);
			add(i, x);
			g[x].push_back(i);
		}
	}
	int s;
	scanf("%d", &s);
	dfs(s);
	for(int i = 1; i <= n; ++i) {
		if(!d[i]) {
			f[i][0] = 1;
			q.push((node){i, 0});
		}
	}
	while(!q.empty()) {
		node h = q.front(); q.pop();
		int len = g[h.x].size();
		for(int i = 0; i < len; ++i) {
			int to = g[h.x][i];
			if(!f[to][h.id ^ 1]) {
				f[to][h.id ^ 1] = 1;
				fr[to][h.id ^ 1] = h.x;
				q.push((node){to, h.id ^ 1});
			}
		}
	}
	// printf("%d\n", maxn);
	if(f[s][1]) {
		printf("Win\n");
		print(s, 1);
	} else if(maxn > 1) {
		printf("Draw\n");
	} else {
		printf("Lose\n");
	}
	return 0;
}