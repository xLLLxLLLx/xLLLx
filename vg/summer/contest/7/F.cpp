#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1001, M = 2e5 + 1;

/* LCT */
struct LCT {
	int f[M], ch[M][2];
	bool rev[M];

	#define ls ch[x][0]
	#define rs ch[x][1]

	bool isroot(int x) {
		return (ch[f[x]][0] != x) && (ch[f[x]][1] != x);
	}

	void Rev(int x) {
		swap(ls, rs);
		rev[x] ^= 1;
	}

	void down(int x) {
		if(rev[x]) {
			Rev(ls), Rev(rs);
			rev[x] = 0;
		}
	}

	void pushdown(int x) {
		if(f[x]) pushdown(f[x]);
		down(x);
	}

	void rotate(int x) {
		int y = f[x], z = f[y], k = (ch[z][1] == y), d = (ch[y][1] == x);
		if(!isroot(y)) {
			ch[z][k] = x;
		}
		f[x] = z;
		ch[y][d] = ch[x][d ^ 1], f[ch[x][d ^ 1]] = y;
		ch[x][d ^ 1] = y, f[y] = x;
	}

	void splay(int x) {
		pushdown(x);
		while(!isroot(x)) {
			int y = f[x], z = f[y];
			if(!isroot(y)) 
				(ch[z][1] == y) ^ (ch[y][1] == x) ? rotate(x) : rotate(y);
			rotate(x);
		}
	}

	void access(int x) {
		for(int y = 0; x; y = x, x = f[x]) {
			splay(x);
			rs = y;
		}
	}

	void makeroot(int x) {
		access(x);
		splay(x);
		Rev(x);
	}

	int findroot(int x) {
		access(x);
		splay(x);
		for(; ls; down(x), x = ls) {
			splay(x);
		}
		return x;
	}

	void split(int x, int y) {
		makeroot(x);
		access(y);
		splay(y);
	}

	void link(int x, int y) {
		makeroot(x), f[x] = y;
	}

	void cut(int x, int y) {
		split(x, y), f[x] = ch[y][0] = 0;
	}
} T;

/* LCT */

/* segtree */

#define lson x << 1
#define rson x << 1 | 1
int sum[M << 2], tag[M << 2], v[M << 2];

int maxn, num;

void up(int x) {
	v[x] = min(v[lson], v[rson]), sum[x] = 0;
	if(v[lson] == v[x]) sum[x] += sum[lson];
	if(v[rson] == v[x]) sum[x] += sum[rson];
}

void down(int x) {	
	if(tag[x]) {
		tag[lson] += tag[x], v[lson] += tag[x];
		tag[rson] += tag[x], v[rson] += tag[x];
		tag[x] = 0;
	}
}

void check(int x) {
	if(v[x] < maxn) {
		maxn = v[x], num = sum[x];
	} else if(v[x] == maxn) {
		num += sum[x];
	}
}

void build(int x, int l, int r) {
	if(l == r) {
		sum[x] = r - l + 1;
		v[x] = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	build(lson, l, mid), build(rson, mid + 1, r);
	up(x);
}

void change(int x, int l, int r, int L, int R, int w) {
	if(L <= l && r <= R) {
		tag[x] += w;
		v[x] += w;
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) change(lson, l, mid, L, R, w);
	if(R > mid) change(rson, mid + 1, r, L, R, w);
	up(x);
}

void ask(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		check(x);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) ask(lson, l, mid, L, R);
	if(R > mid) ask(rson, mid + 1, r, L, R);
	up(x);
}
/* segtree */

int dx[4] = {1, 0, -1, 0};
int dy[4] = {0, 1, 0, -1};
int a[N][N], idx[M], idy[M];

int n, m, nowl = 1, nowr = 1, p[10];

bool judge() {
	p[0] = 0;
	for(int i = 0; i < 4; ++i) {
		int x = idx[nowr + 1] + dx[i], y = idy[nowr + 1] + dy[i];
		if(!x || !y || x > n || y > m || a[x][y] < nowl || a[x][y] > nowr) {
			continue;
		}
		p[++p[0]] = T.findroot(a[x][y]);
	}
	sort(p + 1, p + 1 + p[0]);
	for(int i = 1; i < p[0]; ++i) if(p[i] == p[i + 1]) return false;
	return true;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j) {
			scanf("%d", &a[i][j]);
			idx[a[i][j]] = i, idy[a[i][j]] = j;
		}
	build(1, 1, n * m), change(1, 1, n * m, 1, 1, 1);
	ll ans = 1;
	for(; nowr < n * m; ) {
		for(; nowl < nowr && !judge(); ++nowl) {
			for(int i = 0; i < 4; ++i) {
				int x = idx[nowl] + dx[i], y = idy[nowl] + dy[i];
				if(!x || !y || x > n || y > m || a[x][y] < nowl || a[x][y] > nowr) {
					continue;
				}
				T.cut(nowl, a[x][y]);
			}
		}
		++nowr, change(1, 1, n * m, nowl, nowr, 1);
		for(int i = 0; i < 4; ++i) {
			int x = idx[nowr] + dx[i], y = idy[nowr] + dy[i];
			if(!x || !y || x > n || y > m || a[x][y] < nowl || a[x][y] > nowr) {
					continue;
			}
			T.link(nowr, a[x][y]), change(1, 1, n * m, nowl, a[x][y], -1);
		}
		maxn = 1e9, num = 0;
		ask(1, 1, n * m, nowl, nowr);
		ans += (maxn == 1) * num;
	}
	printf("%I64d\n", ans);
	return 0;
}