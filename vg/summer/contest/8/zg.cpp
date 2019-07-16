#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 10;
struct P {
	ll x, y;
	P () {}
	P (ll _x, ll _y) : x(_x), y(_y) {}
	P operator + (const P &o) {
		return P(x + o.x, y + o.y);
	}
	P operator - (const P &o) {
		return P(x - o.x, y - o.y);
	}
	ll operator * (const P &o) {
		if (!x && !o.x) return 0;
		if (!x) return -y;
		if (!o.x) return o.y;
		if (fabs(1.0 * o.y / o.x - 1.0 * y / x) < 1e-10) {
			return 0;
		}
		if (1.0 * y / x < 1.0 * o.y / o.x) {
			return 1;
		} else {
			return -1;
		}
	}
	bool operator < (const P &o) const {
		return x == o.x ? y < o.y : x < o.x;
	}
} ;
struct E {
	int tot;
	int lnk[N], nxt[N << 1], son[N << 1];
	P w[N << 1];
	E () {
		tot = 1;
	}
	void add (int x, int y, P pt) {
		nxt[++tot] = lnk[x], son[tot] = y, w[tot] = pt, lnk[x] = tot;
	}
	void adde (int x, int y, P pt) {
		add(x, y, pt), add(y, x, pt);
	}
} S, T;
int n, m, k, all, mx, gid, gu, gv;
int cnt, na, nb, s1, s2, qaq;
int las[N], sz[N], dl[N];
P pa[N * 20], qa[N << 3], qb[N << 3], ans[N * 20];

void build (int x, int p) {
	for (int j = S.lnk[x]; j; j = S.nxt[j]) {
		if (S.son[j] != p) {
			T.adde(las[x], ++k, P(0, 0));
			T.adde(k, S.son[j], S.w[j]);
			las[x] = k;
			build(S.son[j], x);
		}
	}
}
void dfs_sz (int x, int p) {
	sz[x] = 1;
	for (int j = T.lnk[x], v; j; j = T.nxt[j]) {
		if (!dl[j >> 1] && T.son[j] != p) {
			dfs_sz(T.son[j], x);
			sz[x] = sz[x] + sz[T.son[j]];
			v = min(sz[T.son[j]], all - sz[T.son[j]]);
			if (mx < v) {
				mx = v;
				gid = j;
				gu = x, gv = T.son[j];
			}
		}
	}
}

void dfs_calc (int x, int p, P pt) {
	if (x <= n) {
		pa[++cnt] = pt;
	}
	for (int j = T.lnk[x]; j; j = T.nxt[j]) {
		if (!dl[j >> 1] && T.son[j] != p) {
			dfs_calc(T.son[j], x, pt + T.w[j]);
		}
	}
}

void making (int &num, P* pt) {
	if (!cnt) {
		num = 0;
		return;
	}
	sort(pa + 1, pa + cnt + 1);
	pt[num = 1] = pa[1];
	for (int i = 2; i <= cnt; ++i) {
		for ( ; num >= 2; --num) {
			if ((pa[i] - pt[num - 1]) * (pt[num] - pt[num - 1]) > 0) {
				break;
			}
		}
		pt[++num] = pa[i];
	}
}

void merge () {
	if (!na || !nb) {
		for (int i = 1, t = max(na, nb); i <= t; ++i) {
			ans[++qaq] = na ? qa[i] : qb[i];
		}
		return;
	}
	ans[++qaq] = qa[1] + qb[1];
	for (int u = 2, v = 2; u <= na || v <= nb; ) {
		if (u > na) {
			ans[++qaq] = qa[u - 1] + qb[v++];
		} else if (v > nb) {
			ans[++qaq] = qa[u++] + qb[v - 1];
		} else {
			P du = qa[u] - qa[u - 1], dv = qb[v] - qb[v - 1];
			if (du * dv < 0) {
				ans[++qaq] = qa[u++] + qb[v - 1];
			} else {
				ans[++qaq] = qa[u - 1] + qb[v++];
			}
		}
	}
}

void divide (int x, int t) {
	if (t == 1) {
		return;
	}
	all = t, mx = gu = gv = 0;
	dfs_sz(x, 0);
  int x1 = gv, s1 = sz[gv], x2 = gu, s2 = all - s1;
	dl[gid >> 1] = 1;
	cnt = 0, dfs_calc(x1, x2, P(0, 0)), making(na, qa);
	cnt = 0, dfs_calc(x2, x1, T.w[gid]), making(nb, qb);
	merge();
	divide(x1, s1);
	divide(x2, s2);
}

ll val (P pt, int sl) {
	return pt.x * sl + pt.y;
}

int main () {
	scanf("%d%d", &n, &m), k = n;
	for (int i = 1, x, y, z1, z2; i < n; ++i) {
		scanf("%d%d%d%d", &x, &y, &z1, &z2);
		S.adde(x, y, P(z1, z2));
	}
	for (int i = 1; i <= n; ++i) {
		las[i] = i;
	}
	
	build(1, 0);
	divide(1, k);
	cnt = qaq;
	memcpy(pa, ans, sizeof pa);
	making(qaq, ans);

	for (int i = 0, cur = 1; i < m; ++i) {
		for ( ; cur < qaq; ++cur) {
			if (val(ans[cur], i) > val(ans[cur + 1], i)) {
				break;
			}
		}
		printf("%lld", val(ans[cur], i));
		putchar(i < m - 1 ? ' ' : '\n');
	}
	return 0;
}