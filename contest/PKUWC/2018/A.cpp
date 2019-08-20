#include <bits/stdc++.h>
using namespace std;
const int T = 1e9;
const int N = 3e5 + 1, M = N * 30, mod = 998244353;
int p;
int a[N], rt[N];
int tag[M], s[M], ls[M], rs[M];
vector <int> g[N];

typedef pair<int, int> P;
vector <P> d;

int mul(int x, int y) {
	return 1ll * x * y % mod;
}

int pf(int x) {
	return mul(x, x);
}

int add(int x, int y) {
	return (x + y) % mod;
}

int sub(int x, int y) {
	return (x - y + mod) % mod;
}

void Mul(int &x, int y) {
	x = mul(x, y);
}

int q_pow(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1)
			ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

int size = 0;

void init() {
	for(int i = 1; i < N * 30; ++i)
		tag[i] = 1;
}

void down(int x) {
	if(tag[x] == 1) return ;
	if(ls[x]) {
		Mul(s[ls[x]], tag[x]);
		Mul(tag[ls[x]], tag[x]);
	}
	if(rs[x]) {
		Mul(s[rs[x]], tag[x]);
		Mul(tag[rs[x]], tag[x]);
	}
	tag[x] = 1;
}

void build(int &x, int l, int r, int L) {
	x = ++size;
	if(l == r) {
		s[x] = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) build(ls[x], l, mid, L);
	else build(rs[x], mid + 1, r, L);
	s[x] = add(s[ls[x]], s[rs[x]]);
}

int merge(int x, int y, int A, int B) {
	// printf("%d %d %d %d\n", x, y, A, B);
	if(!x) {
		if(!A) return y;
		Mul(s[y], A), Mul(tag[y], A);
		return y;
	}
	if(!y) {
		if(!B) return x;
		Mul(s[x], B), Mul(tag[x], B);
		return x;
	}
	down(x), down(y);
	int now = ++size;
	int qxL = add(A, mul(p, s[ls[x]]));
	int qyL = add(B, mul(p, s[ls[y]]));
	int qxR = add(A, mul(sub(1, p), s[rs[x]]));
	int qyR = add(B, mul(sub(1, p), s[rs[y]]));
	ls[now] = merge(ls[x], ls[y], qxR, qyR);
	rs[now] = merge(rs[x], rs[y], qxL, qyL);
	s[now] = add(s[ls[now]], s[rs[now]]);
	return now;
}

void dfs(int x) {
	// printf("%d\n", x);
	if(!(int)g[x].size()) {
		build(rt[x], 1, T, a[x]);
	}
	for(int i = 0; i < (int)g[x].size(); ++i) {
		int to = g[x][i];
		dfs(to);
		p = a[x];
		rt[x] = merge(rt[x], rt[to], 0, 0);
	}
}

void get(int x, int l, int r) {
	if(l == r) {
		d.push_back(P(l, s[x]));
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(ls[x]) get(ls[x], l, mid);
	if(rs[x]) get(rs[x], mid + 1, r);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		if(x)
			g[x].push_back(i);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if((int)g[i].size()) Mul(a[i], q_pow(10000, mod - 2));
	}
	init();
	dfs(1), get(rt[1], 1, T);
	sort(d.begin(), d.end());
	int ans = 0;
	for(int i = 0; i < d.size(); ++i) {
		// printf("gg%d %d\n", d[i].first, d[i].second);
		int pos = mul(i + 1, mul(d[i].first, pf(d[i].second)));
		ans = add(ans, pos);
	}
	printf("%d\n", ans);
	return 0;
}