#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10;

struct segtree {
	#define ls x << 1
	#define rs x << 1 | 1
	int mx[N << 2];

	void clear() {
		memset(mx, 0, sizeof mx);
	}

	void up(int x) {
		mx[x] = max(mx[ls], mx[rs]);
	}

	void upd(int x, int l, int r, int L, int v) {
		if(l == r) {
			mx[x] = max(mx[x], v);
			return ;
		}
		int mid = (l + r) >> 1;
		if(L <= mid) upd(ls, l, mid, L, v);
		else upd(rs, mid + 1, r, L, v);
		up(x);
	}

	int get(int x, int l, int r, int L, int R) {
		if(L > R) return 0;
		if(L <= l && r <= R) {
			return mx[x];
		}
		int mid = (l + r) >> 1, ans1 = 0, ans2 = 0;
		if(L <= mid) ans1 = get(ls, l, mid, L, R);
		if(R > mid) ans2 = get(rs, mid + 1, r, L, R);
		return max(ans1, ans2);
	}

} seg[2];
vector<int> p[N][2];
int n, tot;
int f[N][2], g[N][2], a[N], b[N], d[N], all[N];

int find(int x) {
	return lower_bound(all + 1, all + 1 + tot, x) - all;
}

void work(int f[][2], int a[]) {
	seg[0].clear(), seg[1].clear();
	for(int i = 1; i <= n; ++i) {
		int x = a[i];
		f[i][0] = seg[0].get(1, 1, tot, 1, x - 1) + 1;
		f[i][1] = max(f[i][0], seg[1].get(1, 1, tot, x + 1, tot) + 1);
		seg[0].upd(1, 1, tot, x, f[i][0]);
		seg[1].upd(1, 1, tot, x, f[i][1]);
	}
}

void out() {
	for(int i = 1; i <= d[0]; ++i) {
		printf("%d", d[i]);
		// if(i != d[0]) 
			printf(" ");
	}
	puts("");
	d[0] = 0;
}

bool cmp(int x, int y) {
	return x > y;
}

int main() {
	// freopen("1002.in", "r", stdin);
	while(scanf("%d", &n) == 1) {
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
			all[i] = a[i];
		}
		sort(all + 1, all + 1 + n);
		tot = unique(all + 1, all + 1 + n) - all - 1;
		for(int i = 1; i <= n; ++i) {
			a[i] = find(a[i]);
			b[n - i + 1] = a[i];
		}
		work(f, a), work(g, b);
		for(int i = 1, j = n; i < j; i++, j--) 
			swap(g[i][0], g[j][0]), swap(g[i][1], g[j][1]);
		// printf("!!!\n");
		int maxn = 0;
		for(int i = 1; i <= n; ++i) {
			maxn = max(maxn, f[i][0] + g[i][0] - 1);
		}
		// printf("....%d\n", maxn);
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < 2; ++j)
				p[i][j].clear();
		for(int i = 1; i <= n; ++i) {
			if(f[i][0] + g[i][1] - 1 == maxn) {
				p[f[i][0]][0].push_back(i);
			}
			if(g[i][0] + f[i][1] - 1 == maxn) {
				p[maxn - g[i][0] + 1][1].push_back(i);
			}
		}
		int now = 0, o = 0;
		for(int i = 1; i <= maxn; ++i) {
			int ans1 = n + 1, ans2 = n + 1;
			if(!o) {
				int pos = upper_bound(p[i][0].begin(), p[i][0].end(), now) - p[i][0].begin();
				if(pos < p[i][0].size() && a[p[i][0][pos]] > a[now]) ans1 = p[i][0][pos];
			}
			int pos = upper_bound(p[i][1].begin(), p[i][1].end(), now) - p[i][1].begin();
			if(pos < p[i][1].size() && a[p[i][1][pos]] < a[now]) ans2 = p[i][1][pos];
			now = d[++d[0]] = min(ans1, ans2);
			if(d[d[0]] != ans1) {
				o = 1;
			}
		}
		out();
		now = o = 0;
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < 2; ++j) {
				if(p[i][j].size()) {
					sort(p[i][j].begin(), p[i][j].end(), cmp);
				}
			}
		for(int i = 1; i <= maxn; ++i) {
			// printf("%d\n", now);
			int ans1 = 0, ans2 = 0;
			if(!o) {
				int pos = upper_bound(p[i][0].begin(), p[i][0].end(), now) - p[i][0].begin();
				if(pos < p[i][0].size() && a[p[i][0][pos]] > a[now]) ans1 = p[i][0][pos];
			}
			int pos = upper_bound(p[i][1].begin(), p[i][1].end(), now) - p[i][1].begin();
			// printf("%d\n", pos);
			if(pos < p[i][1].size() && a[p[i][1][pos]] < a[now]) ans2 = p[i][1][pos];
			// printf("%d %d\n", ans1, ans2);
			now = d[++d[0]] = max(ans1, ans2);
			if(d[d[0]] != ans1) {
				o = 1;
			}
		}
		out();
	}
	return 0;
}