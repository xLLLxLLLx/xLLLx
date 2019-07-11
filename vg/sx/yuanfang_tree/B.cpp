#include<bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct data {
	int nt, to;
}a[N << 1][2];
char lx[2];
multiset<int> g[N];
int n, m, t;
int res = 0, top = 0, n1, zd = 0;
int sz[N], s[N], tp[N], f[N], be[N], dep[N], ys[N];
int head[N][2], cnt[2], w[N], dfn[N], low[N], st[N];

void add(int id, int x, int y) {
	a[++cnt[id]][id].to = y;
	a[cnt[id]][id].nt = head[x][id];
	head[x][id] = cnt[id];
}

#define ls x << 1
#define rs x << 1 | 1
int tr[N << 2];

void change(int x, int l, int r, int L, int k) {
	if(l == r) {
		tr[x] = k;
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) {
		change(ls, l, mid, L, k);
	} else {
		change(rs, mid + 1, r, L, k);
	}
	tr[x] = min(tr[ls], tr[rs]);
}

int get(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		return tr[x];
	}
	int mid = (l + r) >> 1, ans1 = 1e9, ans2 = 1e9;
	if(L <= mid) {
		ans1 = get(ls, l, mid, L, R);
	}
	if(R > mid) {
		ans2 = get(rs, mid+1, r, L, R);
	}
	return min(ans1, ans2);
}

void dfs(int u, int fa) {
	dfn[u] = low[u] = ++res;
	st[++top] = u;
	for(int i = head[u][0]; i; i = a[i][0].nt) {
		int to = a[i][0].to;
		if(to == fa) {
			continue;
		}
		if(!dfn[to]) {
			dfs(to, u);
			if(low[to] >= dfn[u]) {
				++ n1;
				add(1, u, n1);
				add(1, n1, u);
				for(;;){
					add(1, st[top], n1);
					add(1, n1, st[top]);
					if(st[top] == to) {
						top--;
						break;
					}
					top--;
				}
			}
			low[u] = min(low[u], low[to]);
		} else {
			low[u] = min(low[u], dfn[to]);
		}
	}
}

void dfs1(int u, int fa) {
	f[u] = fa;
	sz[u] = 1;
	dep[u] = dep[fa] + 1;
	if(u <= n && fa) {
		g[fa].insert(w[u]);
	}
	for(int i = head[u][1]; i; i =a[i][1].nt) {
		int to = a[i][1].to;
		if(to != fa) {
			dfs1(to, u);
			if(sz[s[u]] < sz[to]) {
				s[u] = to;
			}
			sz[u] += sz[to];
		}
	}
}

void dfs2(int u, int fa) {
	be[u] = ++zd;
	ys[zd] = u;
	tp[u] = fa;
	if(s[u]) {
		dfs2(s[u], tp[u]);
	}
	for(int i = head[u][1]; i; i = a[i][1].nt) {
		int to = a[i][1].to;
		if(be[to]) {
			continue;
		}
		dfs2(to, to);
	}
}

int work(int x, int y) {
	int ans = 1e9;
	int fx = tp[x], fy = tp[y];
	for(; fx != fy;) {
		if(dep[fx] > dep[fy]) {
			swap(x, y);
			swap(fx, fy);
		}
		// printf("fy=%d y=%d\n",fy,y);
		// printf("xx%d %d\n",be[fy],be[y]);
		ans = min(ans, get(1, 1, n1, be[fy], be[y]));
		y = f[fy], fy = tp[y];
	}
	if(dep[x] > dep[y]) {
		swap(x, y);
	}
	// printf("%d %d\n",be[x],be[y]);
	ans = min(ans, get(1, 1, n1, be[x], be[y]));
	if(x > n) {
		ans = min(ans, w[f[x]]);
	}
	return ans;
}

void modify(int x, int y) {
	int fa = f[x];
	// printf("aa%d %d\n",x,fa);
	if(fa) {
		g[fa].erase(g[fa].find(w[x]));
		g[fa].insert(y);
		// printf("fabe=%d\n",be[fa]);
		change(1, 1, n1, be[fa], *g[fa].begin());
	}
	w[x] = y;
	// printf("xbe=%d\n",be[x]);
	change(1, 1, n1, be[x], y);
}

int main() {
	scanf("%d%d%d", &n, &m, &t);
	n1 = n;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		add(0, x, y);
		add(0, y, x);
	}
	dfs(1, 0);
	dfs1(1, 0);
	// for(int i = 1; i <= n1; ++i) {
	// 	printf("i=%d sz=%d s=%d\n",i,sz[i],s[i]);
	// }
	dfs2(1, 0);
	for(int i = 1; i <= n; ++i) {
		change(1, 1, n1, be[i], w[i]);
	}
	for(int i = n + 1; i <= n1; ++i) {
		change(1, 1, n1, be[i], *g[i].begin());
	}
	for(int i = 1, x, y; i <= t; ++i) {
		scanf("%s%d%d", lx + 1, &x, &y);
		if(lx[1] == 'A') {
			printf("%d\n", work(x, y));
		} else {
			modify(x, y);
		}
	}
	return 0;
}