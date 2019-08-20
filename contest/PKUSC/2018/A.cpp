#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 6e5 + 10, mod = 998244353;
int tr[N], rt[N], a[N], all[N];
ll jc[N], ny[N];

ll mul(ll x, ll y) {
	return x * y % mod;
}

ll add(ll x, ll y) {
	return (x + y) % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

void init() {
	jc[0] = 1;
	for(int i = 1; i < N; ++i)
		jc[i] = mul(jc[i - 1], i);
	ny[N - 1] = q_pow(jc[N - 1], mod - 2);
	for(int i = N - 1; i >= 1; --i)
		ny[i - 1] = mul(ny[i], i);
	ny[0] = 1;
}

ll C(int x, int y) {
	if(x < y) return 0;
	return mul(jc[x], mul(ny[y], ny[x - y]));
}

int lower(int x) {
	return x & (-x);
}

int num = 0, n, m, tag = 0, k;

int ys(int x) {
	return lower_bound(all + 1, all + 1 + m, x) - all - tag;
}

void upd(int x, int y) {
	if(!x) {
		num++;
		return ;
	}
	for(; x < N; x += lower(x))
		tr[x] += y;
}

void UPD(int x, int y) {
	for(; x; x -= lower(x))
		rt[x] += y;
}

int get(int x) {
	int ans = 0;
	for(; x; x -= lower(x)) 
		ans += tr[x];
	return ans + num;
}

int GET(int x) {
	int ans = 0;
	if(!x) return n;
	for(; x < N; x += lower(x))
		ans += rt[x];
	return ans;
}

int main() {
	// freopen("08.in", "r", stdin);
	init();
	scanf("%d%d", &n, &k);
	int res = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		all[++res] = a[i];
		if(a[i]) {
			all[++res] = a[i] / 2;
			all[++res] = a[i] - 1;
			all[++res] = a[i] * 2;
			all[++res] = a[i] * 2 - 1;
			if(a[i] % 2 == 0)
				all[++res] = a[i] / 2 - 1;
		} else {
			tag = 1;
		}
	}
	// for(int i = 1; i <= n; ++i) {
	// 	printf("%d\n", a[i]);
	// }
	// printf("tag = %d\n", tag);
	sort(all + 1, all + 1 + res);
	m = unique(all + 1, all + 1 + res) - all - 1;
	for(int i = 1; i <= n; ++i) {
		int pos = ys(a[i]);
		upd(pos, 1), UPD(pos, 1);
	}
	for(int i = 1; i <= n; ++i) {
		if(!ys(a[i])) {
			// printf("qwq\n");
			printf("%lld\n", C(n, k));
			continue;
		}
		int mi = a[i] / 2;
		if(a[i] % 2 == 0) mi--;
		int pos = get(ys(mi)) + GET(ys(a[i])) - 1;
		// printf("qwq%d\n", pos);
		ll ans = C(pos, k);
		int delta = GET(ys(a[i])) - GET(ys(a[i] * 2)) - 1;
		int now = get(ys(a[i] * 2 - 1)) - get(ys(a[i] - 1)) - 1;
		// printf("gg%d %d\n", delta, now);
		if(delta < k && now >= delta) {
			ans += mul(C(now, delta), C(n - now - 1, k - delta - 1));
		}
		printf("%lld\n", ans % mod);
	}
	return 0;
}