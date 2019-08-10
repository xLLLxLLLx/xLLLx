#include <bits/stdc++.h>
using namespace std;
const int N = 1200005, mod = 998244353;
int jc[N], ny[N];
int a[N >> 1], vis[N >> 1];

int mul(int x, int y) {
	return 1ll * x * y % mod;
}

int q_pow(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

int C(int x, int y) {
	if(x < y) return 0ll;
	return mul(jc[x], mul(ny[y], ny[x - y]));
}

int cal(int x, int y) {
	if(x < y) return 0ll;
	int dis = 2 * x - y, ans1 = C(dis, x);
	if(y + 2 > dis) return ans1;
	return (ans1 - C(dis, (dis + y) / 2 + 1)) % mod;
}

int main() {
	freopen("inverse.in", "r", stdin);
	freopen("inverse.out", "w", stdout);
	jc[0] = 1;
	for(int i = 1; i < N; ++i)
		jc[i] = mul(jc[i - 1], i);
	ny[N - 1] = q_pow(jc[N - 1], mod - 2);
	for(int i = N - 1; i >= 1; --i)
		ny[i - 1] = mul(ny[i], i);
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		int re = 0, mx = 0, low = 1, he = 0;
		memset(vis, 0, sizeof vis);
		for(int i = 1; i < n; ++i, --he) {
			if(mx < a[i]) he += a[i] - mx;
			mx = max(mx, a[i]);
			for(vis[a[i]] = 1; vis[low]; ++low);
			re = (re + cal(n - i + 1, he + 1)) % mod;
			if(mx > a[i] && a[i] > low) 
				break;
			// printf("%d\n", re);
		}
		printf("%d\n", (re + mod) % mod);
	}
	return 0;
}