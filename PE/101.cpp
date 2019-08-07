#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	for(int i = 1; i <= 11; ++i) {
		printf("ans = %d\n", i);
		ll pos = 1, res = 1;
		for(int j = 1; j <= 10; ++j) {
			res *= 1ll * i;
			res = -res;
			pos += res;
		}
		printf("%lld\n", pos);
	}
	return 0;
}