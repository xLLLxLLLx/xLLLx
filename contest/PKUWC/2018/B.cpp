#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3010, mod = 998244353;
int a[N], b[N];
int jc[N], ny[N], g[2][N], f[2][N];

int mul(int x, int y){
	return 1ll * x * y % mod;
}

int add(int x, int y) {
	return x += y > mod ? x - mod : x;
}

int q_pow(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

void init() {
	jc[0] = ny[0] = 1;
	for(int i = 1; i < N; ++i)
		jc[i] = mul(jc[i - 1], i);
	ny[N - 1] = q_pow(jc[N - 1], mod - 2);
	for(int i = N - 2; i >= 1; --i)
		ny[i] = mul(ny[i + 1], i + 1);
}

bool cmp(int x, int y) {
	return x > y;
}

int C(int x, int y) {
	return mul(jc[x], mul(ny[y], ny[x - y]));
}

void Add(int &x, int y) {
	x = (x + y) % mod;
}

int main() {
	init();
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		memset(f, 0, sizeof f);
		memset(g, 0, sizeof g);
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		for(int i = 1; i <= n; ++i) 
			scanf("%d", &a[i]);
		for(int i = 1; i <= n; ++i)
			scanf("%d", &b[i]);
		sort(a + 1, a + 1 + n, cmp), sort(b + 1, b + 1 + n);
		f[0][0] = 1;
		int now = 0;
		for(int i = 1; i <= n; ++i) {
			now ^= 1;
			for(int j = 0; j <= i; ++j) {
				f[now][j] = f[now ^ 1][j];
				if(j) {
					if(j < k) {
						Add(f[now][j], mul(f[now ^ 1][j - 1], a[i]));
					} else {
						Add(f[now][j], f[now ^ 1][j - 1]);
					}
				}
			}
		}
		now = 0;
		for(int i = 1; i <= n; ++i) {
			now ^= 1;
			for(int j = 0; j <= i; ++j) {
				g[now][j] = g[now ^ 1][j];
				if(m - j < k - 1) 
					Add(g[now][j], g[now ^ 1][j - 1]);
				Add(g[now][j], mul(C(i - 1, j - 1), b[i]));
			}
		}
		// for(int i = 0; i <= n; ++i) {
		// 	printf("%d : f%d : g%d\n", i, f[n & 1][i], g[n & 1][i]);
		// }
		int ans = 0;
		for(int i = 0; i <= min(m, n); ++i) {
			if(m - i <= n) 
				Add(ans, mul(g[n & 1][m - i], f[n & 1][i]));
		}
		printf("%lld\n", ans);
	}
	return 0;
}