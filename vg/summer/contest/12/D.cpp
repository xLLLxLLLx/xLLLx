#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 1e9 + 7, N = 1e6 + 10;
ll b[N], a[N], c[N];

int main() {
	ll n;
	scanf("%lld", &n);
	for(int i = 1; i < N; ++i) {
		a[i] = (a[i - 1] + 1ll * i * i % mod) % mod;
		b[i] = (b[i - 1] + 1ll * i * i * i % mod * i % mod) % mod;
		c[i] = (c[i - 1] + 1ll * i * i * i % mod * i % mod * i % mod * i % mod) % mod;
	}
	ll ans = 0, m = sqrt(n);
	ll M = n % mod;
	for(ll i = 1, j = m; i <= m; ++i) {
		for(; i * i + j * j > n; --j);
		ll k = i * i % mod;
		ans = (ans + (1 + M - k) * (2 + M - k) % mod * (M + 2ll * k) % mod * (j + 1)) % mod;
		ans = (ans + (4 + M * 3 - k * 12 % mod - 6ll * M * k % mod + 6ll * k * k + 2ll * mod) % mod * a[j]) % mod;
		ans = (ans + (k * 6 - 3 * M % mod - 6ll + 2ll * mod) % mod * b[j] + 2ll * c[j]) % mod;
	}
  ans = ans * 2 % mod * (mod + 1) / 3 % mod;
  ans = (ans + M * (M + 1) % mod * (M + 2) % mod * (mod + 1) / 6) % mod;
  cout << ans << endl;
	return 0;
}