#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll inf = 10000;

int main() {
	srand(time(NULL));
	int n = 1;
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i) {
		ll x = rand() % inf + 1, y = rand() % inf + 1;
		printf("%lld %lld\n", x, y);
	}
	return 0;
}