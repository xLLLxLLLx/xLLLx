#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
	freopen("matrix.in", "r", stdin);
	freopen("matrix.out", "w", stdout);
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= m; ++i) {
		scanf("%d%d", &x, &y);
		a[x]++, a[y]++;
	}	
	ll ans = 0;
	for(int i = 1; i <= n; ++i) {
		ans += 1ll * a[i] * a[i];
	}
	printf("%d\n", ans);
	return 0;
}