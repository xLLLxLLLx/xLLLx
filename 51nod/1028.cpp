#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int mod = 998244353;
const int N = (1 << 22);
int rev[N];
ll A[N], B[N], g[N];
char lx[N];

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = ans * x % mod;
		x = x * x % mod;
	}
	return ans;
}

void ntt(ll a[N], int n) {
	for(int i = 0; i < n; ++i)
		if(rev[i] > i) 
			swap(a[i], a[rev[i]]);
	for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1)
		for(int i = 0; i < n; i += (d << 1))
			for(int j = 0; j < d; ++j) {
				ll tmp = g[t * j] * a[i + j + d] % mod;
				a[i + j + d] = (a[i + j] - tmp + mod) % mod;
				a[i + j] = (a[i + j] + tmp) % mod;
			}
}

int main() {
	int xx;scanf("%d", &xx);
	scanf("%s", lx);
	int lena = strlen(lx);
	for(int i = 0; i < lena; ++i) {
		int pos = lx[i] - '0';
		A[lena - i - 1] = pos;
	}
	scanf("%s", lx);
	int lenb = strlen(lx);
	for(int i = 0; i < lenb; ++i) {
		int pos = lx[i] - '0';
		B[lenb - i - 1] = pos;
	}
	int n = 1, L = 0;
	for(; n <= lena + lenb; n <<= 1, L++) ;
	g[0] = 1, g[1] = q_pow(3, (mod - 1) / n);
	// printf("%lld %lld\n", g[0], g[1]);
	for(int i = 2; i < n; ++i) {
		g[i] = g[i - 1] * g[1] % mod;
	}
	for(int i = 0; i < n; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | (i & 1) << (L - 1);
	}
	ntt(A, n), ntt(B, n);
	g[1] = q_pow(g[1], mod - 2);
	for(int i = 2; i < n; ++i) {
		g[i] = g[i - 1] * g[1] % mod;
	}
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i] % mod;
	}
	ntt(A, n);
	ll pos = q_pow(n, mod - 2);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * pos % mod;
	}
	for(int i = 0; i < n; ++i) {
		A[i + 1] += A[i] / 10;
		A[i] %= 10;
	}
	while(!A[n] && n) n--;
	for(int i = n; i >= 0; --i) {
		printf("%d", A[i]);
	}
	return 0;
}