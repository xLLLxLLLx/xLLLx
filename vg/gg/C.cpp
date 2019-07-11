#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
struct data {
	int nt, to;
}a[N<<1];
ll d[N];
int n;
int head[N], sz[N], cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	sz[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
		sz[u] += sz[to];
	}
	d[1] += sz[u];
}

void Dfs(int u, int fa) {
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		d[to] = d[u] + n - 2ll * sz[to];
		Dfs(to, u);
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	Dfs(1, 0);
	ll maxn = 0;
	for(int i = 1; i <= n; ++i) {
		// printf("%lld\n", d[i]);
		maxn = max(maxn, d[i]);
	}
	printf("%lld\n", maxn);
	return 0;
}