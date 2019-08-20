#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 25, M = (1 << 20), mod = 998244353;
ll a[N], fr[M], rf[M], v[M];

ll mul(ll x, ll y) {
	return x * y % mod;
}

void Mul(ll &x, ll y) {
	x = (x * y) % mod;
}

ll add(ll x, ll y) {
	return (x + y) % mod;
}

void Add(ll &x, ll y) {
	x = (x + y) % mod;
}

int n, tot;

void pre() {
	for(int i = 0; i <= tot; ++i) {
		for(int j = 0; j < n; ++j) {
			if((i >> j) & 1) 
				v[i] += a[j];
		}
		// printf("v[%d]=%lld\n", i, v[i]);
	}
}

int main() {
	scanf("%d", &n);
	tot = (1 << n) - 1;
	for(int i = 0; i < n; ++i) {
		scanf("%lld", &a[i]);
	}
	pre();
	fr[0] = 1;
	for(int i = 0; i <= tot; ++i) {
		if(!fr[i]) continue;
		for(int j = 0; j < n; ++j) {
			if((i >> j) & 1) {
				continue;
			}
			if(v[i | (1 << j)] >= 0)
				Add(fr[i | (1 << j)], fr[i]);
		}
	}
	rf[0] = 1;
	for(int i = 0; i <= tot; ++i) {
		if(!rf[i]) continue;
		for(int j = 0; j < n; ++j) {
			if((i >> j) & 1) continue;
			if(v[i | (1 << j)] < 0)
				Add(rf[i | (1 << j)], rf[i]);
		}
	}
	// for(int i = 0; i < tot; ++i) {
	// 	printf("%d %lld %lld\n", i, fr[i], rf[i]);
	// }
	ll sum = 0;
	for(int i = 0; i <= tot; ++i) {
		int pos = tot ^ i;
		for(int j = 0; j < n; ++j) {
			if((i >> j) & 1) continue;
			Add(sum, mul(v[i] + a[j], mul(fr[i], rf[pos ^ (1 << j)])));
			// printf("qwq%lld %lld %lld\n", v[i] + a[j], fr[i], rf[tot ^ (1 << j)]);
		}
	}
	printf("%lld\n", (sum + mod) % mod);
	return 0;
}