#include <bits/stdc++.h>
#define ll long long 
using namespace std;
const int mod = 1e9 + 7;
map<ll, ll> mp;

ll work(ll x) {
	if(mp.count(x)) return mp[x];
	return mp[x] = ((work(x / 2) + work((x - 1) / 2)) % mod + work((x - 2) / 2)) % mod;
}

int main() {
	ll n;
	mp[0] = 1, mp[1] = 2;
	scanf("%lld", &n);
	printf("%lld\n", work(n));
	return 0;
}