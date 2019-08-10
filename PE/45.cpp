#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<ll, int> p1, p2, p3;

ll js1(int x) {
	return 1ll * x * (x + 1) / 2;
}

ll js2(int x) {
	return 1ll * x * (3 * x - 1) / 2;
}

ll js3(int x) {
	return 1ll * x * (2 * x - 1);
}

int main() {
	int maxn = 1e5;
	for(int i = 1; i <= maxn; ++i) {
		p1[js1(i)] = 1;
	}
	for(int i = 1; i <= maxn; ++i) {
		p2[js2(i)] = 1;
	}
	for(int i = 1;; ++i) {
		ll pos = js3(i);
		if(p1[pos] && p2[pos]) {
			printf("%lld\n", pos);
		}
	}
	return 0;
}