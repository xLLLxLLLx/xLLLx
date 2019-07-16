#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;

struct P {
	ll x, y;
	
	P() { x = y = 0; }
	P(ll _x, ll _y) { x = _x, y = _y; }
	
	P operator + (P C) { return P(x + C.x, y + C.y); }
	P operator - (P C) { return P(x - C.x, y - C.y); }

	ll operator * (P C) {
		if(!x && !C.x) return 0ll;
		if(!x) return -y;
		if(!C.x) return C.y;
		if(x * C.y == y * C.x) return 0ll;
		if(1.0 * y / x < 1.0 * C.y / C.x) return 1;
		else return -1;
	}

	bool operator < (P &C) const {
		return x == C.x ? y < C.y : x < C.x;
	}
} pa[N * 20], ans[N * 20], qa[N * 10], qb[N * 10];

struct E {
	int head[N], Next[N << 1], to[N << 1], tot;
	P w[N << 1];
	
	E() { tot = 1; }

	void add(int x, int y, P p) {
		to[++tot] = y;
		w[tot] = p;
		Next[tot] = head[x];
		head[x] = tot;
	}

	void adde(int x, int y, P p) {
		add(x, y, p), add(y, x, p);
	}
} S, T;

int fr[N], us[N], sz[N];
int n, m, now, na, nb, mx, bu, bv, bid, tot, len, cnt;

void build(int x, int fa) {
	for(int i = S.head[x]; i; i = S.Next[i]) {
		int to = S.to[i];
		if(to == fa) {
			continue;
		}
		T.adde(fr[x], ++now, P(0, 0));
		T.adde(now, to, S.w[i]);
		fr[x] = now;
		build(to, x);
	}
}

void gotsz(int x, int fa) {
	sz[x] = 1;
	for(int i = T.head[x]; i; i = T.Next[i]) {
		int to = T.to[i];
		if(us[i >> 1] || to == fa) {
			continue;
		}
		gotsz(to, x);
		sz[x] += sz[to];
		int pos = min(tot - sz[to], sz[to]);
		if(mx < pos) {
			bu = x, bv = to, bid = i;
			mx = pos;
		}
	}
}

void gotpoint(int x, int fa, P p) {
	if(x <= n) {
		pa[++cnt] = p;
	}
	for(int i = T.head[x]; i; i = T.Next[i]) {
		int to = T.to[i];
		if(us[i >> 1] || to == fa) {
			continue;
		}
		gotpoint(to, x, p + T.w[i]);
	}
}

void MakeConvex(int &num, P *q) {
	if(!cnt) {
		num = 0;
		return ;
	}
	sort(pa + 1, pa + 1 + cnt);
	q[num = 1] = pa[1];
	for(int i = 2; i <= cnt; ++i) {
		for( ; num >= 2; --num) {
			if((pa[i] - q[num - 1]) * (q[num] - q[num - 1]) > 0) {
				break;
			}
		}
		q[++num] = pa[i];
	}
}

void merge() {
	if(!na || !nb) {
		int L = max(na, nb);
		for(int i = 1; i <= L; ++i) {
			ans[++len] = na ? qa[i] : qb[i];
		}
		return ;
	}
	ans[++len] = qa[1] + qb[1];
	for(int u = 2, v = 2; u <= na || v <= nb; ) {
		if(u > na) {
			ans[++len] = qa[u - 1] + qb[v++];
		} else if(v > nb) {
			ans[++len] = qa[u++] + qb[v - 1];
		} else {
			P du = qa[u] - qa[u - 1], dv = qb[v] - qb[v - 1];
			if(du * dv < 0) {
				ans[++len] = qa[u++] + qb[v - 1];
			} else {
				ans[++len] = qa[u - 1] + qb[v++];
			}
		}
	}
}

void go(int x, int size) {
	if(size == 1) {
		return ;
	}
	tot = size, mx = bu = bv = 0;
	gotsz(x, 0);
	int x1 = bv, s1 = sz[bv], x2 = bu, s2 = tot - s1;
	us[bid >> 1] = 1;
	cnt = 0, gotpoint(x1, x2, P(0,0)), MakeConvex(na, qa);
	cnt = 0, gotpoint(x2, x1, T.w[bid]), MakeConvex(nb, qb);
	merge();
	go(x1, s1);
	go(x2, s2);
}

ll js(P x, ll y) {
	return x.x * y + x.y;
}

int main() {
	scanf("%d%d", &n, &m);
	now = n;
	for(int i = 1, x, y, A, B; i < n; ++i) {
		scanf("%d%d%d%d", &x, &y, &A, &B);
		S.adde(x, y, P(A, B));
	}
	for(int i = 1; i <= n; ++i) {
		fr[i] = i;
	}
	build(1, 0);
	go(1, now);
	cnt = len;
	memcpy(pa, ans, sizeof pa);
	MakeConvex(len, ans);
	for(int i = 0, cur = 1; i < m; ++i) {
		for( ; cur < len; ++cur) 
			if(js(ans[cur], i) > js(ans[cur + 1], i)) {
				break;
			}
		printf("%lld", js(ans[cur], i));
		putchar(i < m - 1 ? ' ' : '\n');
	}
	return 0;
}