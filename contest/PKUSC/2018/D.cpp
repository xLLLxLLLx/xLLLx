#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10, LOG = 21 + 1, inf = 1e9;
ll f[N][LOG + 1], s[N][LOG + 1];
int a[N];

ll gcd(ll x, ll y) {
	return y ? gcd(y, x % y) : x;
}

ll work(int x, int L) {
	if(a[x] <= L) return x - L;
	ll now = 1, ans = x - a[x];
	x = a[x];
	for(int i = LOG; i >= 0; --i) {
		if(f[x][i] >= L) {
			ans += s[x][i] + (x - f[x][i]) * now;
			now += (1 << i);
			x = f[x][i];
		}
	}
	return ans + (x - L) * (now + 1);
}

int main() {
	int n;
	scanf("%d", &n);
	a[0] = 1;
	for(int i = 2; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	f[n + 1][0] = inf;
	for(int i = n; i >= 1; --i) {
		f[i][0] = min(1ll * a[i], f[i + 1][0]);
		s[i][0] = i - f[i][0];
	}
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= n; ++i) {
			f[i][j] = f[f[i][j - 1]][j - 1];
			s[i][j] = s[i][j - 1] + s[f[i][j - 1]][j - 1];
			s[i][j] += (f[i][j - 1] - f[f[i][j - 1]][j - 1]) << (j - 1);
		}
	int q;
	scanf("%d", &q);
	for(int o = 1, l, r, x; o <= q; ++o) {
		scanf("%d%d%d", &l, &r, &x);
		ll pos = work(x, l) - work(x, r + 1);
		ll tmp = r - l + 1;
		ll gg = gcd(pos, tmp);
		printf("%lld/%lld\n", pos / gg, tmp / gg);
	}
	return 0;
}