#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10, M = 2e6 + 10;
int a[M][2];

int main() {
	int n, now = 0;
	scanf("%d", &n);
	ll ans = 0;
	a[0][0]++;
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		now ^= x;
		int pos = i & 1;
		ans += a[now][pos];
		a[now][pos]++;
		// printf("%d %d\n", i, now);
	}
	printf("%lld\n", ans);
	return 0;
}