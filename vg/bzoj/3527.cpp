#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
const int N = (1 << 18);
struct C {
	double r, i;
	C() { r = i = 0; }
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i * x.r); }
} f[N], _f[N], g[N], w[N];
int rev[N];

void fft(C a[N], int n) {
	for(int i = 0; i < n; ++i)
		if(rev[i] > i)
			swap(a[i], a[rev[i]]);
	for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1)
		for(int i = 0; i < n; i += (d <<1))
			for(int j = 0; j < d; ++j) {
				C tmp = w[t * j] * a[i + j + d];
				a[i + j + d] = a[i + j] - tmp;
				a[i + j] = a[i + j] + tmp;
			}
}

int main() {
	int m;
	scanf("%d", &m);
	for(int i = 0; i < m; ++i) {
		scanf("%lf", &f[i].r);
		_f[m - i - 1].r = f[i].r;
		if(i) g[i].r = (1.0 / i / i);
	}
	int n = 1, L = 0;
	for(; n < 2 * m; n <<= 1, L++) ;
		// printf("%d %d\n", n, L);
	for(int i = 0; i < n; ++i) {
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	fft(f, n), fft(_f, n), fft(g, n);
	for(int i = 0; i < n; ++i) {
		f[i] = f[i] * g[i];
		_f[i] = _f[i] * g[i];
		w[i].i = -w[i].i;
	}
	fft(f, n), fft(_f, n);
	for(int i = 0; i < m; ++i) {
		printf("%.5f\n", (f[i].r / n - _f[m - i - 1].r / n));
	} 
	return 0;
}