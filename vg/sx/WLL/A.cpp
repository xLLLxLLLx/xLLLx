#include <bits/stdc++.h>
using namespace std;
const int M = 2e5 + 10, N = 2e3 + 10, inf = 1e9;
struct data {
	int fr, to, c, nt;
} a[M << 1];
queue<int> q;
int head[N], v[N], w[N], dep[N], cur[N];
int cnt = -1, S, T;

void add(int x, int y, int c) {
	printf("%d %d %d\n", x, y, c);
	a[++cnt] = (data) {x, y, c, head[x]};
	head[x] = cnt;
	a[++cnt] = (data) {y, x, 0, head[y]};
	head[y] =cnt;
}

int bfs() {
	memset(dep, 0, sizeof dep);
	dep[S] = 1;
	q.push(S);
	while(!q.empty()) {
		int h = q.front(); q.pop();
		for(int i = head[h]; ~i; i = a[i].nt) {
			int to = a[i].to;
			if(!dep[to] && a[i].c) dep[to] = dep[h] + 1, q.push(to);
		}
	}
	return dep[T];
}

int dfs(int now, int v) {
	if(now == T) return v;
	for(int &i = cur[now]; ~i; i = a[i].nt) {
		int to = a[i].to;
		if(dep[to] == dep[now] + 1 && a[i].c) {
			int d = dfs(to, min(a[i].c, v));
			if(d) {
				a[i].c -= d;
				a[i ^ 1].c += d;
				return d;
			}
		}
	}
	return 0;
}

void init() {
	cnt = -1;
	memset(head, -1, sizeof head);
}

int main() {
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	S = 0, T = n + m + 1;
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &w[i]);
		add(i, T, w[i]);
	}
	for(int i = 1, num, pos; i <= n; ++i) {
		scanf("%d", &num);
		for(int j = 1, x; j <= num; ++j) {
			scanf("%d", &w[j]);
		}
		scanf("%d", &pos);
		for(int j = 1; j <= num; ++j) {
			add(S, i + m, pos);
			add(i + m, w[j], inf);
		}
	}
	int ans = 0;
	for(; bfs(); ) {
		for(int i = S; i <= T; ++i) 
			cur[i] = head[i];
		for(; int d = dfs(1, inf); ) 
			ans += d;
	}
	printf("%d\n", ans);
	return 0;
}