#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		ll n, k;
		scanf("%lld%lld", &n, &k);
		ll pos = n / k;
		if(pos % k) {
			printf("YES\n");
		} else {
			printf("NO\n");
		}
	}
	return 0;
}