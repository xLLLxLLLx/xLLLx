#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data {
	int nt, to;
} a[N << 1];
struct node {
	int l, r, mx;
	ll v;
	node() {
		l = r = v = mx = 0;
	}
} tr[N * 60];
ll d[N];
int n;
int w[N], head[N], rt[N], cnt = 0, now = 0;

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

int merge(int A, int B, int l, int r) {
	if(!A) return B;
	if(!B) return A;
	int pos = ++now;
	if(l == r) {
		tr[pos].mx = tr[A].mx + tr[B].mx;
		tr[pos].v = l;
		return pos;
	}
	int mid = (l + r) >> 1;
	tr[pos].l = merge(tr[A].l, tr[B].l, l, mid);
	tr[pos].r = merge(tr[A].r, tr[B].r, mid + 1, r);
	tr[pos].mx = max(tr[tr[pos].l].mx, tr[tr[pos].r].mx);
	if(tr[tr[pos].l].mx == tr[pos].mx) {
		tr[pos].v += tr[tr[pos].l].v;
	}
	if(tr[tr[pos].r].mx == tr[pos].mx) {
		tr[pos].v += tr[tr[pos].r].v;
	}
	return pos;
}

void put(int x, int l, int r, int L) {
	if(l == r) {
		if(tr[x].mx < 1) {
			tr[x].mx = 1;
			tr[x].v = L;
		} else {
			tr[x].mx ++;
		}
		return ;
	} 
	int mid = (l + r) >> 1;
	if(L <= mid) {
		if(!tr[x].l) tr[x].l = ++now;
		put(tr[x].l, l, mid, L);
	} else {
		if(!tr[x].r) tr[x].r = ++now;
		put(tr[x].r, mid + 1, r, L);
	}
	if(!tr[x].l) {
		tr[x].mx = tr[tr[x].r].mx;
		tr[x].v = tr[tr[x].r].v;
	}
	else if(!tr[x].r) {
		tr[x].mx = tr[tr[x].l].mx;
		tr[x].v = tr[tr[x].l].v;
	}
	else {
		// printf("!!!\n");
		tr[x].mx = max(tr[tr[x].l].mx, tr[tr[x].r].mx);
		tr[x].v = 0;
		if(tr[tr[x].l].mx == tr[x].mx) {
			tr[x].v += tr[tr[x].l].v;
		}
		if(tr[tr[x].r].mx == tr[x].mx) {
			tr[x].v += tr[tr[x].r].v;
		}
	}
}

void dfs(int u, int fa) {
	rt[u] = ++now;
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
		rt[u] = merge(rt[u], rt[to], 1, n);
	}
	// printf("qwq%d %d\n", u, tr[rt[u]].v);
	// printf("%d %d\n", tr[rt[u]].l, tr[rt[u]].r);
	put(rt[u], 1, n, w[u]);
	// printf("%d\n", tr[rt[u]].v);
	d[u] = tr[rt[u]].v;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &w[i]);
	}
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	for(int i = 1; i <= n; ++i) {
		printf("%lld ", d[i]);
	}
	return 0;
}