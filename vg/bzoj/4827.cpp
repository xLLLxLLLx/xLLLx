#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double PI = acos(-1.0);
const int N = (1 << 20);
struct C {
	double r, i;
	C(){ r = 0, i = 0; }
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i *x.r); }
} A[N], B[N], w[N];
int rev[N], x[N], y[N];

void fft(C a[], int n) {
	for(int i = 0; i < n; ++i) 
		if(rev[i] > i)
			swap(a[i], a[rev[i]]);
	for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1)
		for(int i = 0; i < n; i += (d << 1))
			for(int j = 0; j < d; ++j) {
				C tmp = w[t * j] * a[i + j + d];
				a[i + j + d] = a[i + j] - tmp;
				a[i + j] = a[i + j] + tmp;
			}
}

ll cal(ll x, ll y, ll z) {
	return x * z * z + y * z;
}

ll get(ll x, ll y) {
	ll c = - y / (2ll * x), d = c + 1, e = c - 1;
	return min(cal(x, y, c), min(cal(x, y, d), cal(x, y, e)));
}

int main() {
	int m, k;
	scanf("%d%d", &m, &k);
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &x[i]);
	}
	for(int i = 1; i <= m; ++i) {
		scanf("%d", &y[i]);
	}
	ll gg = 0, ans = 0;
	for(int i = 1; i <= m; ++i) {
		gg += 2ll * (x[i] - y[i]);
		ans += 1ll * x[i] * x[i];
		ans += 1ll * y[i] * y[i];
	}
	ans += get(m, gg);
	for(int i = 0; i < m; ++i) {
		A[m - i - 1].r = x[i + 1];
		B[i].r = B[i + m].r = y[i + 1];
	}
	int n = 1, L = 0;
	for(; n < 3 * m; n <<= 1, L++) ;
	for(int i = 0; i < n; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
	}
	fft(A, n), fft(B, n);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i];
		w[i].i = -w[i].i;
	}
	fft(A, n);
	ll maxn = 0;
	for(int i = m - 1; i < 2 * m; ++i) {
		maxn = max(maxn, (ll)(A[i].r / n + 0.5));
	}
	ans -= 2ll * maxn;
	printf("%lld\n", ans);
	return 0;
}
