#include <bits/stdc++.h>
using namespace std;
const int N = 1e7, M = 8e6 + 1;
struct data {
	int nt, to;
} a[N];
int n, m;
queue<int> q;
int head[M], vis[M], vs[M], cnt = 0;
int v[M];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	vis[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa || vis[to]) {
			continue;
		}
		dfs(to, u);
	}
}

int main() {
	scanf("%d%d", &n, &m);
	int tot = (1 << n) - 1;
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &v[i]);
		add(i, v[i] + m + 1);
		add((tot ^ v[i]) + m + 1, i);
		q.push(v[i]), vs[v[i]] = 1;
	}
	while(!q.empty()) {
		int h = q.front(); q.pop();
		for(int i = 0; i < n; ++i) {
			if((h >> i) & 1) {
				continue;
			}
			int pos = h | (1 << i);
			add(h + m + 1, pos + m + 1);
			if(!vs[pos]) {
				vs[pos] = 1;
				q.push(pos);
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= m; ++i) {
		if(!vis[i]) {
			ans++;
			dfs(i, 0);
		}
	}
	printf("%d\n", ans);
	return 0;
}