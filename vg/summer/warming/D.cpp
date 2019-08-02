#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 998244353, M = 35;
struct data {
	int a[M];
} q[N];
ll pw[M], b[M];

void Mul(ll &x, ll y) {
	x = x * y % mod;
}

void Add(ll &x, ll y) {
	x = (x + y) % mod;
}

ll mul(ll x, ll y) {
	return x * y % mod;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		for(; x; x /= 10) q[i].a[++q[i].a[0]] = x % 10;
		b[q[i].a[0]]++;
	}
	pw[0] = 1;
	for(int i = 1; i < M; ++i) pw[i] = pw[i - 1] * 10 % mod;
	ll ans = 0;
	for(int i = 1; i <= n; ++i) {
		ll pos = 0;
		for(int j = 1; j <= q[i].a[0]; ++j) {
			Add(pos, mul(q[i].a[j], pw[j * 2 - 1]));
			Add(pos, mul(q[i].a[j], pw[j * 2 - 2]));
		}
		ll res = 0;
		for(int j = q[i].a[0] + 1; j < M; ++j) {
			res += b[j];
		}
		Mul(pos, res);
		for(int j = 1; j <= q[i].a[0]; ++j) {
			ll tmp = 0;
			for(int k = 1; k <= j; ++k) {
				Add(tmp, mul(pw[k * 2 - 2], q[i].a[k]));
				Add(tmp, mul(pw[k * 2 - 1], q[i].a[k]));
			}
			for(int k = j + 1; k <= q[i].a[0]; ++k) {
				Add(tmp, mul(pw[j + k - 1], mul(q[i].a[k], 2ll)));
			}
			Add(pos, mul(tmp, b[j]));
		}
		Add(ans, pos);
	}
	printf("%lld\n", ans);
	return 0;
}