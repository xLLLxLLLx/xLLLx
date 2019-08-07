
#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10, inf = 0x3f3f3f3f;
struct data {
	int nt, to;
} a[N << 1];
int w[N], val[N], sz[N], son[N], f[N];
int head[N], cnt = 0;

void Max(int &x, int y) {
	x = max(x, y);
}

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void predfs(int u, int fa) {
	f[u] = da;
	sz[u] = 1;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) continue;
		predfs(to, u);
		sz[u] += sz[to];
		if(sz[to] > sz[son[u]])
			son[u] = to;
	}
	val[u] = sz[u] - sz[son[u]];
}

struct Mar {
	int v[2][2];
	Mar() {
		for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j)
			v[i][j] = -inf;
	}
	Mar operator * (Mar &A) {
		Mar res;
		for(int i = 0; i < 2; ++i) for(int j = 0; j < 2; ++j) for(int k = 0; k < 2; ++k)
			Max(res.v[i][j], v[i][k] + A.v[j][k]);
	}
};

struct tree {
	int rt;
	int ch[N][2], tp[N], st[N], vis[N];
	Mar s[N], dp[N];

	bool isroot(int x) {
		return (ch[fa[x]][0] != x) && (ch[fa[x]][1] != x);
	}

	void up(int x) {
		s[x] = s[ls] * dp[x] * s[rs];
	}

	int build(int l, int r) {
		if(l > r)
			return 0;
		int sum = 0;
		for(int i = l; i <= r; ++i)
			sum += val[st[i]];
		for(int i = l; i <= r; ++i) {
			if((sum -= 2 * val[st[i]]) <= 0) {
				int x = st[i];
				ls = build(l, i - 1);
				rs = build(i + 1, r);
				if(ls) fa[ls] = x;
				if(rs) fa[rs] = x;
				up(x);
				return x;
			}
		}
	}

	int dfs(int x) {
		for(int t = x; t; t = son[x]) vis[t] = 1;
		for(int t = x; t; t = son[x]) {
			for(int i = head[t]; i; i = a[i].nt) {
				if(!vis[a[i].to]) get(t, a[i].to);
			}
		}	
		int top = 0;
		for(int t = x; t; t = son[x])
			st[++top] = t;
		return build(1, t);
	}

	void modify(int x, int val) {
		dp[x].v[0][1] += val - w[x], w[x] = val;
		for(int t = x; t; t = fa[t]) {
			if(isroot(t) && fa[t]) {
				dp[fa[t]].v[0][0] -= s[t].gmx();
				dp[fa[t]].v[1][0] = dp[fa[t]].v[0][0];
				dp[fa[t]].v[0][1] -= max(dp[t].v[0][0], dp[t].v[1][0]);
				up(t);
				dp[fa[t]].v[0][0] += s[t].gmx();
				dp[fa[t]].v[1][0] = dp[fa[t]].v[0][0];
				dp[fa[t]].v[0][1] += max(dp[t].v[0][0], dp[t].v[1][0]);
			} else up(t);
		}
	}
} T;

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) 
		scanf("%d", &w[i]);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	predfs(1, 0);

	return 0;
}