#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e7 + 1;
int pr[664585];
bool vis[N];

void init() {
	vis[0] = vis[1] = 1;
	for(int i = 2; i < N; ++i) {
		if(!vis[i]) pr[++pr[0]] = i;
		for(int j = 1; j <= pr[0]; ++j) {
			if(i * pr[j] >= N) break;
			vis[i * pr[j]] = 1;
			if(i % pr[j] == 0) break;
		}
	}
}

ll q_pow(ll x, ll y, ll mod) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = (__int128)ans * x % mod;
		x = (__int128)x * x % mod;
	}
	return ans;
}

bool check(ll x) {
	if(x < N) return vis[x] == 0;
	for(int i = 1; i <= pr[0] && 1ll * pr[i] * pr[i] <= x; ++i) {
		if(x % pr[i] == 0) return 0;
	}
	return 1;
}

ll find(ll p) {
	while(!check(p)) --p;
	return p;
}

int main() {
	init();
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		ll p;
		scanf("%lld", &p);
		ll q = find(p - 1);
		ll ans = p - 1;
		for(ll i = p - 1; i > q; --i) {
			ans = (__int128)ans * q_pow(i, p - 2, p) % p;
		}
		printf("%lld\n", ans);
	}
	return 0;
}