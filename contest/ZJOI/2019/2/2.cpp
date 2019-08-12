#include <bits/stdc++.h>
#define ls tr[x].l
#define rs tr[x].r
#define ll long long
using namespace std;
const int N = 3e5 + 10, LOG = 20;
int n, m;
struct data {
	int nt, to;
} a[N << 1];
int head[N], dep[N], f[N], dfn[N], be[N], res = 0, cnt = 0;
int ou[N << 1];
struct node {
	int l, r, mx, mn, cov, sum;
} tr[N * 20];
int num = 0, rt[N], st[N << 1][LOG + 1];
ll ans = 0;
vector<int> g[N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void predfs(int u, int fa) {
	dep[u] = dep[fa] + 1, f[u] = fa;
	dfn[u] = ++res, ou[++ou[0]] = u;
	be[u] = ou[0];
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		predfs(to, u);
		ou[++ou[0]] = u;
	}
}

void init() {
	for(int i = 1; i <= ou[0]; ++i) st[i][0] = ou[i];
  for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= ou[0]; ++i) {
			if(i + (1 << j) > ou[0] + 1)
				continue;
			if(dfn[st[i][j - 1]] > dfn[st[i + (1 << (j - 1))][j - 1]])
				st[i][j] = st[i + (1 << (j - 1))][j - 1];
			else
				st[i][j] = st[i][j - 1];
		}
}

int GetLCA(int l, int r) {
	l = be[l], r = be[r];
	if(l > r)
		swap(l, r);
	int k = (int)(log(double(r - l + 1)) / log(2.0));
	if(dfn[st[l][k]] < dfn[st[r - (1 << k) + 1][k]])
		return st[l][k];
	else
		return st[r - (1 << k) + 1][k];
}

void up(int x) {
	tr[x].mx = tr[rs].mx ? tr[rs].mx : tr[ls].mx;
	tr[x].mn = tr[ls].mn ? tr[ls].mn : tr[rs].mn;
	tr[x].sum = tr[ls].sum + tr[rs].sum;
	if(tr[ls].mx && tr[rs].mn)
		tr[x].sum -= dep[GetLCA(tr[ls].mx, tr[rs].mn)];
}

void modify(int &x, int l, int r, int L, int v) {
	if(!x) 
		x = ++num;
	if(l == r) {
		tr[x].cov += v;
		if(tr[x].cov)
			tr[x].mn = tr[x].mx = L, tr[x].sum = dep[L];
		else
			tr[x].mn = tr[x].mx = tr[x].sum = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	if(dfn[L] <= mid)
		modify(ls, l, mid, L, v);
	else 
		modify(rs, mid + 1, r, L, v);
	up(x);
}

int merge(int x, int y, int l, int r) {
	if(!x || !y) 
		return x + y;
	if(l == r) {
		tr[x].cov += tr[y].cov;
		if(tr[x].cov) {
			tr[x].mx = tr[x].mn = max(tr[x].mn, tr[y].mn);
			tr[x].sum = dep[tr[x].mn];
		} else {
			tr[x].mn = tr[x].mx = tr[x].sum = 0;
		}
		return x;
	}
	int mid = (l + r) >> 1;
	ls = merge(ls, tr[y].l, l, mid);
	rs = merge(rs, tr[y].r, mid + 1, r);
	up(x);
	return x;
}

void dfs(int x) {
	for(int i = head[x]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == f[x])
			continue;
		dfs(to);
		rt[x] = merge(rt[x], rt[to], 1, n);
	}
	for(int i = 0; i < g[x].size(); ++i)
		modify(rt[x], 1, n, g[x][i], -2);
	if(tr[rt[x]].mn && tr[rt[x]].mx)
		ans += tr[rt[x]].sum - dep[f[GetLCA(tr[rt[x]].mn, tr[rt[x]].mx)]] - 1;
}

int main() {
	freopen("in2", "r", stdin);
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	predfs(1, 0), init();
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		int lca = GetLCA(x, y);
		modify(rt[x], 1, n, x, 1);
		modify(rt[x], 1, n, y, 1);
		modify(rt[y], 1, n, x, 1);
		modify(rt[y], 1, n, y, 1);
		if(f[lca]) 
			g[f[lca]].push_back(x), g[f[lca]].push_back(y);
	}
	dfs(1);
	printf("%lld\n", ans / 2);
	return 0;
}
