#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
struct data {
	int l, r;
} a[N], b[N];
ll f[N << 2][3];
int all[N << 2], nx[N << 2][2];
int k, n, m, tot, cnt = 0;

ll add(ll x, ll y) {
	return (x + y + mod) % mod;
}

ll mul(ll x, ll y) {
	return (x * y) % mod;
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

void Min(int &x, int y) {
	x = min(x, y);
}

int get(int x) {
	return lower_bound(all + 1, all + 1 + tot, x) - all;
}

int main() {
	scanf("%d%d%d", &k, &n, &m);
	all[++cnt] = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].l, &a[i].r);
		a[i].l--;
		all[++cnt] = a[i].l, all[++cnt] = a[i].r;
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%d%d", &b[i].l, &b[i].r);
		b[i].l--;
		all[++cnt] = b[i].l, all[++cnt] = b[i].r;
	}
	all[++cnt] = k;
	sort(all + 1, all + 1 + cnt);
	tot = unique(all + 1, all + 1 + cnt) - all - 1;
	for(int i = 1; i <= tot; ++i) {
		nx[i][0] = nx[i][1] = tot + 1;
	}
	for(int i = 1; i <= n; ++i) {
		a[i].l = get(a[i].l), a[i].r = get(a[i].r);
		Min(nx[a[i].l][0], a[i].r);
	}
	for(int i = 1; i <= m; ++i) {
		b[i].l = get(b[i].l), b[i].r = get(b[i].r);
		Min(nx[b[i].l][1], b[i].r);
	}
	for(int i = tot - 1; i >= 1; --i) {
		Min(nx[i][0], nx[i + 1][0]);
		Min(nx[i][1], nx[i + 1][1]);
	}
	f[tot][0] = f[tot][1] = f[tot][2] = 1;
	for(int i = tot - 1; i >= 1; --i) {
		ll g0 = add(f[i + 1][0], -f[nx[i][0]][0]);
		ll g1 = add(f[i + 1][1], -f[nx[i][1]][1]);
		ll g2 = mul(f[i + 1][2], add(q_pow(2, all[i + 1] - all[i]), -2));
		f[i][0] = add(f[i + 1][0], add(g1, g2));
		f[i][1] = add(f[i + 1][1], add(g0, g2));
		f[i][2] = add(g0, add(g1, g2));
	}
	printf("%lld\n", f[1][2]);
	return 0;
}