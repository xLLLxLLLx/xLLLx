#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	ll n, m;
	cin >> n >> m;
	ll pos = 1;
	for(int i = 1; i <= n; ++i) {
		pos *= 2;
		if(pos > m) {
			return printf("%lld\n", m), 0;
		}
	}
	printf("%lld\n", m % pos);
	return 0;
}