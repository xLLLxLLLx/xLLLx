#include <bits/stdc++.h>
#define ll long long
using namespace std;

ll get(ll x, ll y) {
	return y ? get(y, x % y) : x;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		ll x, y, z, w;
		cin >> x >> y >> z >> w;
		x += -z, y += -w;
		x = max(x, -x), y = max(y, -y);
		ll gcd = get(x, y);
		printf("Case %d: %lld\n", o, gcd + 1);
	}
	return 0;
}