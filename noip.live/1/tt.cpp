#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	ll x;
	cin >> x;
	ll len = sqrt(x);
	for(int i = 2; i <= len; ++i) {
		if(x % i == 0) {
			int pos = 0;
			while(x % i == 0) {
				x /= i;
				pos++;
			}
			printf("%d %d\n", i, pos);
		}
	}
	if(x > 1) printf("%lld %d\n", x, 1);
	return 0;
}