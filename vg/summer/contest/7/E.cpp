#include <bits/stdc++.h>
#define ll long long
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int N = 1e5 + 10;
ll tr[N << 2][20], tag[N << 2], sum[N << 2];
int yz[15], c[15], val[N];
int mod, phi;

ll mul(ll x, ll y) {
	return x * y % mod;
}

ll add(ll x, ll y) {
	return (x + y) % mod;
}

void Add(ll &x, ll y) {
	x = (x + y) % mod;
}

void Mul(ll &x, ll y) {
	x = (x * y) % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) Mul(ans, x);
		Mul(x, x);
	}
	return ans;
}

ll rev(ll x) {
	return q_pow(x, phi - 1);
}

void getphi(int x) {
	int len = sqrt(x);
	phi = x;
	for(int i = 2; i <= len; ++i) {
		if(x % i == 0) {
			yz[++yz[0]] = i;
			phi = phi / i * (i - 1);
			while(x % i == 0) x /= i;
		}
	}
	if(x > 1) yz[++yz[0]] = x, phi = phi / x * (x - 1);
}

void get(int x, int &y) {
	memset(c, 0, sizeof c);
	for(int i = 1; i <= yz[0]; ++i) {
		while(x % yz[i] == 0) {
			x /= yz[i], c[i]++;
		}
	}
	y = x % mod;
}

ll cal(int x) {
	ll ans = 1;
	for(int i = 1; i <= yz[0]; ++i) {
		Mul(ans, q_pow(yz[i], tr[x][i]));
	}
	return ans;
}

void up(int x) {
	sum[x] = add(sum[ls], sum[rs]);
}

void down(int x) {
	ll pos = cal(x);
	for(int i = 1; i <= yz[0]; ++i) {
		tr[ls][i] += tr[x][i];
		tr[rs][i] += tr[x][i];
		tr[x][i] = 0;
	}
	Mul(tag[ls], tag[x]), Mul(sum[ls], mul(tag[x], pos));
	Mul(tag[rs], tag[x]), Mul(sum[rs], mul(tag[x], pos));
	tag[x] = 1;
}

void build(int x, int l, int r) {
	tag[x] = 1;
	if(l == r) {
		sum[x] = val[l] % mod;
		for(int i = 1; i <= yz[0]; ++i) {
			while(val[l] % yz[i] == 0) {
				val[l] /= yz[i];
				tr[x][i]++;
			}
		}
		tag[x] = val[l] % mod;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	up(x);
}

void modify(int x, int l, int r, int L, int R, ll real, ll v) {
	if(L <= l && r <= R) {
		for(int i = 1; i <= yz[0]; ++i) {
			tr[x][i] += c[i];
		}
		Mul(tag[x], v);
		Mul(sum[x], real);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) modify(ls, l, mid, L, R, real, v);
	if(R > mid) modify(rs, mid + 1, r, L, R, real, v);
	up(x);
}

void change(int x, int l, int r, int L, ll v) {
	if(l == r) {
		for(int i = 1; i <= yz[0]; ++i) {
			tr[x][i] -= c[i];
		}
		Mul(tag[x], rev(v));
		sum[x] = mul(cal(x), tag[x]);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) change(ls, l, mid, L, v);
	else change(rs, mid + 1, r, L, v);
	up(x);
}

ll ask(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		return sum[x];
	}
	down(x);
	int mid = (l + r) >> 1;
	ll ans1 = 0, ans2 = 0;
	if(L <= mid) ans1 = ask(ls, l, mid, L, R);
	if(R > mid) ans2 = ask(rs, mid + 1, r, L, R);
	return add(ans1, ans2);
}

int main() {
	int n;
	scanf("%d%d", &n, &mod);
	getphi(mod);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &val[i]);
	}
	build(1, 1, n);
	int q;
	scanf("%d", &q);
	for(int i = 1; i <= q; ++i) {
		int opt;
		scanf("%d", &opt);
		if(opt == 1) {
			int l, r, real, v;
			scanf("%d%d%d", &l, &r, &real);
			get(real, v);
			modify(1, 1, n, l, r, real, v);
		} else if(opt == 2) {
			int p, real, v;
			scanf("%d%d", &p, &real);
			get(real, v);
			change(1, 1, n, p, v);
		} else {
			int l, r;
			scanf("%d%d", &l, &r);
			printf("%lld\n", ask(1, 1, n, l, r) % mod);
		}
	}
	return 0;
}