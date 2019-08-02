#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10;
ll b[N];
int a[N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	ll ans = 0;
	int cnt = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if(i > 1) b[++cnt] = a[i - 1] - a[i];
	}
	sort(b + 1, b + 1 + cnt);
	for(int i = 1; i <= k - 1; ++i) {
		ans += b[i];
	}
	ans += (a[n] - a[1]);
	printf("%lld\n", ans);
	return 0;
}