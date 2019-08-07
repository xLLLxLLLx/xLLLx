#include <bits/stdc++.h>
#define ll long long
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int mod = 998244353, inv = (mod + 1) / 2;

int add(int x, int y) {
	return (x += y) > mod ? x - mod : x;
}

int mul(int x, int y) {
	return (long long)x * y % mod;
}

int sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}

const int N = 1e5 + 10;
int sum = 0;
int p[N << 2], q[N << 2], k[N << 2], b[N << 2];

void build(int x, int l, int r) {
	k[x] = 1;
	if(l == r) {
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
}

void down(int x) {
	q[ls] = add(mul(k[x], q[ls]), b[x]);
	b[ls] = add(mul(k[x], b[ls]), b[x]);
	k[ls] = mul(k[x], k[ls]);
	q[rs] = add(mul(k[x], q[rs]), b[x]);
	b[rs] = add(mul(k[x], b[rs]), b[x]);
	k[rs] = mul(k[x], k[rs]);
	k[x] = 1, b[x] = 0;
}

void modify(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		sum = sub(sum, p[x]);
		p[x] = add(mul(inv, p[x]), inv);
		q[x] = add(mul(inv, q[x]), inv);
		b[x] = add(mul(inv, b[x]), inv);
		k[x] = mul(inv, k[x]);
		sum = add(sum, p[x]);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	sum = sub(sum, p[x]);
	p[x] = mul(inv, p[x]);
	q[x] = mul(inv, q[x]);
	sum = add(sum, p[x]);
	if(R <= mid) {
		modify(ls, l, mid, L, R);
		sum = sub(sum, p[rs]);
		p[rs] = mul(inv, add(p[rs], q[rs]));
		sum = add(sum, p[rs]);
	} else if(L > mid) {
		sum = sub(sum, p[ls]);
		p[ls] = mul(inv, add(p[ls], q[ls]));
		sum = add(sum, p[ls]);
		modify(rs, mid + 1, r, L, R);
	} else {
		modify(ls, l, mid, L, R), modify(rs, mid + 1, r, L, R);
	}
}

int main() {
	int n, m, w = 1;
	scanf("%d%d", &n, &m);
	build(1, 1, n);
	for(int o = 1, opt; o <= m; ++o) {
		scanf("%d", &opt);
		if(opt == 1) {
			int l, r;
			scanf("%d%d", &l, &r);
			modify(1, 1, n, l, r);
			(w *= 2) %= mod;
		} else {
			printf("%d\n", mul(sum, w));
		}
	}
	return 0;
}