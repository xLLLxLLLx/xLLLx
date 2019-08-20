#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e6 + 10;
const double PI = acos(-1.0);
char lx[N];

struct C {
	double r, i;
	C() {}
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C &A) { return C(r + A.r, i + A.i); }
	C operator - (C &A) { return C(r - A.r, i - A.i); }
	C operator * (C &A) { return C(r * A.r - i * A.i, r * A.i + i * A.r); }
} a[N], b[N], w[N];
ll v[N];
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

void gotFTT(C a[], C b[], int n, int L) {
	for(int i = 0; i < n; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
		w[i] = C(cos(2.0 * PI / n * i), sin(2.0 * PI / n * i));
	}
	fft(a, n), fft(b, n);
	for(int i = 0; i < n; ++i) {
		w[i].i = -w[i].i;
		a[i] = a[i] * b[i];
	}
	fft(a, n);
	for(int i = 0; i < n; ++i) {
		v[i] = (long long)(a[i].r / n + 0.5);
	}
}

int main() {
	// freopen("in", "r", stdin);
	scanf("%s", lx);
	int len = strlen(lx);
	for(int i = 0; i < len; ++i) {
		a[i].r = (lx[i] == '0');
		b[i].r = (lx[i] == '1');
	}
	int n = 1, L = 0;
	reverse(b, b + len);
	for(; n < 2 * len; n <<= 1, L++);
	gotFTT(a, b, n, L);
	// for(int i = 0; i < n; ++i)
	// 	printf("%d ", v[i]);
	ll ans = 1ll * len * len;
	for(int i = 1; i < len; ++i) {
		int flg = 0;
		for(int j = i; j < len; j += i) 
			if(v[len - 1 + j] || v[len - 1 - j]) flg = 1;
		if(!flg) ans ^= 1ll * (len - i) * (len - i);
	}
	printf("%lld\n", ans);
	return 0;
}