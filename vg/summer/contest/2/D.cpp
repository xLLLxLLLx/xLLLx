#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
}a[N << 1];
int ans[N], dp[N], mx[N][2];
int head[N], f[N], id[N], res = 0, cnt = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	f[u] = fa;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
	}
	id[++res] = u;
}

int cal(int x) {
	if(~ans[x]) return ans[x];
	for(int o = 1; o <= res; ++o) {
		int u = id[o];
		dp[u] = mx[u][0] = mx[u][1] = 0;
		for(int i = head[u]; i; i = a[i].nt) {
			int v = a[i].to;
			if(v == f[u]) {
				continue;
			}
			dp[u] += dp[v];
			if(mx[v][0] > mx[u][0]) {
				mx[u][1] = mx[u][0], mx[u][0] =mx[v][0];
			} else if(mx[v][0] > mx[u][1]) {
				mx[u][1] = mx[v][0];
			}
		}
		if(mx[u][0] + mx[u][1] + 1 >= x) {
			dp[u]++;
			mx[u][0] = 0, mx[u][1] = 0;
		} else {
			mx[u][0]++;
			mx[u][1]++;
		}
	}
	return ans[x] = dp[1];
}

void work(int l, int r) {
	if(l == r) {
		ans[l] = cal(l);
		return ;
	}
	if(cal(l) == cal(r)) {
		for(int i = l; i <= r; ++i) {
			ans[i] = ans[l];
		}
		return ;
	}
	int mid = (l + r) >> 1;
	work(l, mid), work(mid + 1, r);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	memset(ans, -1, sizeof ans);
	work(1, n);
	for(int i = 1; i <= n; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}