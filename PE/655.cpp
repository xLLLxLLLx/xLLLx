#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 40;
int a[N];

bool check(ll x) {
	int n = 0; 
	for(; x; x /= 10) a[++n] = x % 10;
	for(int i = 1; i <= n; ++i) {
		if(a[i] != a[n - i + 1])
			return false;
	}
	return true;
}

int main() {
	int n = 109;
	int ans = 0;
	ll maxn = 100000;
	for(int i = 1; ; ++i) {
		ll pos = 1ll * i * n;
		if(pos > maxn) break;
		// printf("n%lld\n", pos);
		if(check(pos)) {
			printf("%lld\n", pos);
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}