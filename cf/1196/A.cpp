#include <bits/stdc++.h>
#define ll long long
using namespace std;
ll a[5];

int main() {
	int q;
	cin >> q;
	for(int o = 1; o <= q; ++o) {
		ll sum = 0, x;
		for(int i = 1; i <= 3; ++i) {
			cin >> x;
			sum += x;
		}
		printf("%lld\n", sum / 2);
	}
	return 0;
}