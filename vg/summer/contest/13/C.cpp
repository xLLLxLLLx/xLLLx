#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 100;
int c[N], mx[N], v[N], w[N];

int main() {
	int n, L;
	scanf("%d%d" , &n, &L);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &c[i]);
	}
	memset(mx, 0x3f, sizeof mx);
	int cnt = 0;
	for(int i = 1; i <= n; ++i) {
		mx[i] = min(mx[i], c[i]);
		for(int j = i + 1; j <= n; ++j) {
			if(1ll * c[i] * (1 << (j - i)) < c[j]) {
				mx[j] = min(mx[j], c[i] * (1 << (j - i)));
			}
		}
	}
	for(int i = n - 1; i >= 1; --i) mx[i] = min(mx[i], mx[i + 1]);
	// for(int i = 1; i <= n; ++i) {
	// 	printf("%d\n", mx[i]);
	// }
	ll ans = 0, maxn = 1e18;
	int pos = 1 << (n - 1), now = n;
	while(L) {
		ans += 1ll * (L / pos) * mx[now];
		maxn = min(maxn, ans + mx[now]);
		L %= pos;
		pos >>= 1, now--;
	}
	ans = min(ans, maxn);
	printf("%lld\n", ans);
	return 0;
}