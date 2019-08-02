#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 55;
ll f[N];
ll a[N], b[N];

int main() {
	int n, m;
	cin >> n >> m;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i]);
	}
	for(int i = 1; i <= n; ++i) f[i] = -1e18;
	for(int i = 1; i <= m; ++i) {
		scanf("%lld", &b[i]);
	}
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= m; ++j) {
			f[i] = max(f[i], a[i] * b[j]);
		}
	}
	sort(f + 1, f + 1 + n);
	printf("%lld\n", f[n - 1]);
	return 0;
}