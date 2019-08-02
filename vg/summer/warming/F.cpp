#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
const ll inf = 2e9 + 10;
struct data {
	int l, r;
} Q[N], sr[N];

vector<ll> g[N];
vector<int> f[N], h[N];

int tr[N << 2], d[N], bf[N], ans = 0;
ll all[N];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

ll js(ll x, ll y) {
	return x * inf + y;
}

#define ls x << 1
#define rs x << 1 | 1

void change(int x, int l, int r, int L, int R) {
	if(x == 1) printf("%d %d %d %d %d\n", x, l, r, L, R);
	if(L > R) return ;
	if(L <= l && r <= R) {
		tr[x]++;
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) change(ls, l, mid, L, R);
	if(R > mid) change(rs, mid + 1, r, L, R);
}

void get(int x, int l, int r, int L, int R) {
	ans += tr[x];
	if(L <= l && r <= R) {
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) get(ls, l, mid, L, R);
	if(R > mid) get(rs, mid + 1, r, L, R);
}

int main() {
	int n, tot = 0;
	scanf("%d", &n);
	for(int i = 1, num; i <= n; ++i) {
		scanf("%d", &num);
		for(int j = 1; j <= num; ++j) {
			scanf("%d%d", &sr[j].l, &sr[j].r);
		}
		sr[num + 1] = sr[1];
		for(int j = 1; j <= num; ++j) {
			int x = sr[j + 1].l - sr[j].l, y = sr[j + 1].r - sr[j].r; 
			int pos = gcd(x, y);
			pos = max(pos, -pos);
			x /= pos, y /= pos;
			all[++tot] = js(x, y);
			printf("qwq%d %d\n", x, y);
			g[i].push_back(all[tot]);
		}
	}
	sort(all + 1, all + 1 + tot);
	int m = unique(all + 1, all + 1 + tot) - all - 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < g[i].size(); ++j) {
			int pos = lower_bound(all + 1, all + 1 + m, g[i][j]) - all;
			f[i].push_back(pos);
		}
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < f[i].size(); ++j) {
			printf("%d ", f[i][j]);
		}
		puts("");
	}
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) {
		scanf("%d%d", &Q[i].l, &Q[i].r);
		h[Q[i].r].push_back(i);
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j < f[i].size(); ++j) {
			change(1, 1, m, bf[f[i][j]] + 1, i);
			bf[f[i][j]] = i;
		}
		for(int j = 0; j < h[i].size(); ++j) {
			ans = 0;
			get(1, 1, m, Q[h[i][j]].l, i);
			d[h[i][j]] = ans;
		}
	}
	for(int i = 1; i <= q; ++i) {
		printf("%d\n", d[i]);
	}
	return 0;
}