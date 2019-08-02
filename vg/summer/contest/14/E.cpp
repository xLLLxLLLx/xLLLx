#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
const double PI = acos(-1.0);
struct C {
	double r, i;
	C() { r = 0, i = 0; }
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, i * x.r + r * x.i); }
} A[N], B[N], w[N];
char lx[N];
int rev[N], b[N], d[N];
 
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
 
void work(int len) {
	int L = 0, n = 1;
	for(; n < 2 * len; n <<= 1, L++);
	for(int i = 0; i < n; ++i) {
		b[i] = 0;
		A[i] = B[i] = C(0, 0);
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
	}
	for(int i = 1; i <= len; ++i) {
		if(lx[i] == 'V') A[len - i].r = 1;
		if(lx[i] == 'K') B[i - 1].r = 1;
	}
	fft(A, n), fft(B, n);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i];
		w[i].i = -w[i].i;
	}
	fft(A, n);
	for(int i = 0; i < n; ++i) {
		int pos = int((A[i].r + 0.5) / n);
		// printf("%d\n", pos);
		if(pos) b[abs(i - len + 1)] = 1;
	}
	int ans = 0;
	for(int i = 1; i <= len; ++i) {
		if(!b[i]) {
			for(int j = i; j <= len; j += i) {
				if(b[j]) {
					b[i] = 1;
					break;
				}
			}
		}
	}
	d[0] = 0;
	for(int i = 1; i <= len; ++i)
		if(!b[i])
			d[++d[0]] = i;
	printf("%d\n", d[0]);
	for(int i = 1; i <= d[0]; ++i) {
		printf("%d ", d[i]);
	}
	puts("");
}
 
int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1, len; o <= T; ++o) {
		scanf("%d%s", &len, lx + 1);
		work(len);
	}
	return 0;
}