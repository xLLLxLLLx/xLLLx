#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 18;
struct data {
	int w, id;
}a[N * 60], q[N];

namespace LCT {
	int ch[N][2], f[N], sz[N];

	bool isroot(int x) {
		return (ch[f[x]][0] != x) && (ch[f[x]][1] != x);
	}

	void up(int x) {
		sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
	}

	void rotate(int x) {
		int y = f[x], z = f[y], d = (ch[y][1] == x), k = (ch[z][1] == y);
		if(!isroot(y)) {
			ch[z][k] = x;
		}
		f[x] = z;
		ch[y][d] = ch[x][d ^ 1], f[ch[x][d ^ 1]] = y;
		ch[x][d ^ 1] = y, f[y] = x;
		up(y);
	}

	void splay(int x) {
		while(!isroot(x)) {
			int y = f[x], z = f[y];
			if(!isroot(y)) {
				(ch[y][0] == x) ^ (ch[z][0] == y) ? rotate(x) : rotate(y);
			}
			rotate(x);
		}
		up(x);
	}

	void access(int x) {
		int y = 0;
		for(; x; y = x, x = f[x]) {
			splay(x);
			ch[x][1] = y;
			up(x);
		}
	}

	void link(int x, int y) {
		access(x);
		splay(x);
		f[x] = y;
	}

	void cut(int x) {
		access(x);
		splay(x);
		ch[x][0] = f[ch[x][0]] = 0;
		up(x);
	}

	int findroot(int x) {
		access(x);
		splay(x);
		for(; ch[x][0]; x = ch[x][0]);
		splay(x);
		return x;
	}

	data ask(int x) {
		x = findroot(x);
		return (data){x, sz[x]};
	}
}

int v[N], r[N], nmin[N], nmax[N];

namespace ST {
	int minn[N][LOG + 1], maxn[N][LOG + 1];

	void pre(int n) {
		for(int i = 1; i <= n; ++i) {
			minn[i][0] = maxn[i][0] = nmin[i] = nmax[i] = v[i];
		}
		for(int i = 1; i <= LOG; ++i) {
			for(int j = 1; j <= n; ++j) {
				if(j + (1 << i) > n + 1) break;
				minn[j][i] = min(minn[j][i - 1], minn[j + (1 << (i - 1))][i - 1]);
				maxn[j][i] = max(maxn[j][i - 1], maxn[j + (1 << (i - 1))][i - 1]);
			}
		}
	}

	int jump(int x, int d, int n) {
		for(int i = LOG; i >= 0; --i) {
			if(r[x] + (1 << i) <= n && max(nmax[x], maxn[r[x] + 1][i]) - min(nmin[x], minn[r[x] + 1][i]) <= d) {
				nmin[x] = min(nmin[x], minn[r[x] + 1][i]);
				nmax[x] = max(nmax[x], maxn[r[x] + 1][i]);
				r[x] += (1 << i);
			}
		}
		return r[x];
	}
}

int bsz = 50;
int cnt = 0, now = 1;

void upd(int d, int n) {
	while(now <= cnt && a[now].w <= d) {
		int x = a[now++].id;
		r[x]++;
		nmin[x] = min(nmin[x], v[r[x]]);
		nmax[x] = max(nmax[x], v[r[x]]);
		LCT::cut(x);
		if(r[x] <= n && r[x] - x <= bsz) {
			LCT::link(x, r[x] + 1);
		}
	}
}

int ask(int d, int n) {
	int x = 1, ans = 0;
	while(x <= n) {
		if(LCT::f[x]) {
			data t = LCT::ask(x);
			ans += t.id - 1;
			x = t.w;
		} else {
			x = ST::jump(x, d, n) + 1;
			ans++;
		}
	}
	return ans - 1;
}

int da[N];

bool cmp(data A, data B) {
	return A.w == B.w ? A.id < B.id : A.w < B.w;
}

int main() {
	int n, w, k;
	scanf("%d%d%d", &n, &w, &k);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &v[i]);
	}
	for(int i = 1; i <= n; ++i) {
		r[i] = i;
		LCT::sz[i] = 1;
		LCT::link(i, i + 1);
	}
	ST::pre(n);
	for(int i = 1; i <= n; ++i) {
		int minn = v[i], maxn = v[i];
		for(int j = 1; j <= bsz + 1 && i + j <= n; ++j) {
			minn = min(minn, v[i + j]);
			maxn = max(maxn, v[i + j]);
			a[++cnt] = (data){maxn - minn, i};
		}
	}
	sort(a + 1, a + 1 + cnt, cmp);
	for(int i = 1, x; i <= k; ++i) {
		scanf("%d", &x);
		q[i] = (data){w - x, i};
	}
	sort(q + 1, q + 1 + k, cmp);
	for(int i = 1; i <= k; ++i) {
		upd(q[i].w, n);
		da[q[i].id] = ask(q[i].w, n);
	}
	for(int i = 1; i <= k; ++i) {
		printf("%d\n", da[i]);
	}
	return 0;
}