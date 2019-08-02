#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 25;
int p[N], r[N];

ll q_pow(ll x, int y, int mod) {
	x %= mod;
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = ans * x % mod;
		x = x * x % mod;
	}
	return ans;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		ll sum = 1;
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d", &p[i], &r[i]);
			sum *= p[i];
		}
		// printf("sum = %lld\n", sum);
		ll ans = 0;
		for(int i = 1; i <= n; ++i) {
			ll tmp = q_pow(sum / p[i], p[i] - 2, p[i]);
			// printf("%lld\n", tmp);
			tmp = tmp * r[i] % sum * (sum / p[i]) % sum;
			ans = (ans + tmp) % sum;
		}
		ans = (ans % sum + sum) % sum;
		printf("Case %d: %lld\n", o, ans);
	}
	return 0;
}