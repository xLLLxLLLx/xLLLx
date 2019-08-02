#include <bits/stdc++.h>
#define ll long long
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int N = 1e5 + 10;
vector<int> g[N];
int n, c, k;
int mx[N << 2], s[N << 2], tag[N << 2];

void down(int x) {
	if(tag[x]) {
		mx[ls] += tag[x], tag[ls] += tag[x];
		mx[rs] += tag[x], tag[rs] += tag[x];
		tag[x] = 0;
	}
}

void up(int x) {
	mx[x] = max(mx[ls], mx[rs]);
	s[x] = (mx[x] == mx[ls]) ? s[ls] : s[rs];
}

void build(int x, int l, int r) {
	s[x] = l;
	mx[x] = c, tag[x] = 0;
	if(l == r) {
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
}

void upd(int x, int l, int r, int L, int R, int v) {
	// if(x == 1) {
	// 	printf("L = %d, R = %d, v = %d\n", L, R, v);
	// }
	if(L <= l && r <= R) {
		mx[x] += v;
		tag[x] += v;
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) upd(ls, l, mid, L, R, v);
	if(R > mid) upd(rs, mid + 1, r, L, R, v);
	up(x);
	// printf("x=%d l=%d r=%d mx=%d s=%d\n", x, l, r, mx[x], s[x]);
}

int Ask(int x, int l, int r, int L, int R) {
	if(mx[x] != c) return 0;
	if(L <= l && r <= R) return s[x];
	int mid = (l + r) >> 1;
	down(x);
	if(R <= mid) return Ask(ls, l, mid, L, R);
	if(L > mid) return Ask(rs, mid + 1, r, L, R);
	int t = Ask(ls, l, mid, L, R);
	if(t) return t;
	return Ask(rs, mid + 1, r, L, R);
}

int main() {
	while(scanf("%d%d%d", &n, &c, &k) == 3) {
		build(1, 1, n);
		int ans = 0;
		for(int i = 1; i <= c; ++i) {
			g[i].clear();
			g[i].push_back(0);
		}
		for(int i = 1, x; i <= n; ++i) {
			// printf("%d\n", i);
			scanf("%d", &x);
			if(x <= c) {
				upd(1, 1, n, g[x].back() + 1, i, -1);
				g[x].push_back(i);
				int p = g[x].size() - k;
				if(p >= 1) {
					upd(1, 1, n, g[x][p - 1] + 1, g[x][p], 1);
				}
			}
			int j = Ask(1, 1, n, 1, i);
			if(j) ans = max(ans, i - j + 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}