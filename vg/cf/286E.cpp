#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
const int N = (1 << 22);
struct C {
	double r, i;
	C() { r = i = 0; }
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i * x.r); }
} a[N], w[N];
int rev[N], b[N], d[N];

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
	int num, m;
	scanf("%d%d", &num, &m);
	for(int i = 1, x; i <= num; ++i) {
		scanf("%d", &x);
		a[x].r = 1;
		b[x] = 1;
	}
	a[0].r = 1;
	int n = 1, L = 0;
	for(; n <= (m + 1) * 2; n <<= 1, L++) ;
	for(int i = 0; i < n; ++i) {
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	fft(a, n);
	for(int i = 0; i < n; ++i) {
		w[i].i = -w[i].i;
		a[i] = a[i] * a[i];
	}
	fft(a, n);
	for(int i = 1; i <= m; ++i) {
		int pos = (int)(a[i].r / n + 0.5);
		// printf("%d %d\n", i, pos);
		if(pos) {
			if(!b[i]) return printf("NO\n"), 0;
			if(pos == 2) {
				d[++d[0]] = i;
			}
		}
	}
	printf("YES\n%d\n", d[0]);
	for(int i = 1; i <= d[0]; ++i) {
		printf("%d ", d[i]);
	}
	return 0;
}