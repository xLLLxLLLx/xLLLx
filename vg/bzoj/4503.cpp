#include <bits/stdc++.h>
using namespace std;
const int N = (1 << 18);
const double PI = acos(-1.0);
struct C {
	double r, i;
	C() { r = i = 0; }
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i * x.r); }
} A[N], B[N], A2[N], A3[N], B2[N], B3[N], a[N], b[N], c[N], w[N];
char lx[N]; 
int rev[N], d[N], ans[N];

void fft(C a[N], int n) {
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

int main() {
	scanf("%s", lx);
	int lenx = strlen(lx);
	for(int i = 0; i < lenx; ++i) {
		A[i].r = lx[i] - 'a' + 1;
	}
	scanf("%s", lx);
	int leny = strlen(lx);
	for(int i = 0; i < leny; ++i) {
		int pos = lx[i] - 'a' + 1;
		if(lx[i] == '?') pos = 0;
		B[leny - i - 1].r = pos;
	}
	int n = 1, L = 0;
	for(;n <= lenx + leny; n <<= 1, L++);
	for(int i = 0; i < n; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		A2[i] = A[i] * A[i];
		A3[i] = A2[i] * A[i];
		B2[i] = B[i] * B[i];
		B3[i] = B2[i] * B[i];
		// if(i <= 5) {
		// 	cout<<"a3="<<A3[i].r <<"a2="<<A2[i].r<<"a1="<<A1[i].r<<endl;
		// }
	}
	fft(A, n), fft(A2, n), fft(A3, n), fft(B, n), fft(B2, n), fft(B3, n);
	for(int i = 0; i < n; ++i) {
		a[i] = A3[i] * B[i];
		b[i] = A2[i] * B2[i];
		c[i] = A[i] * B3[i];
		w[i].i = -w[i].i;
	}
	fft(a, n), fft(b, n), fft(c, n);
	// printf("%d\n", n);
	for(int i = 0; i < n; ++i) {
		d[i] = (int)(a[i].r - 2.0 * b[i].r + c[i].r + 0.5);
		// printf("%d ", d[i]);
	}
	// puts("");
	for(int i = leny - 1; i < lenx; ++i) {
		if(!d[i]) {
			ans[++ans[0]] = i - leny + 1;
		}
	}
	printf("%d\n", ans[0]);
	for(int i = 1; i <= ans[0]; ++i) {
		printf("%d\n", ans[i]);
	}
	return 0;
}