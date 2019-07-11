#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double PI = acos(-1.0);
const int N = (1 << 20);
struct C {
	double r, i;
	C() { r = i = 0; }
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, i * x.r + r * x.i); }
} A[N], B[N], w[N];
int rev[N], a[N], b[N];
ll f[N];

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

void work(int l, int r) {
	// x = y
	if(l == r) {
		f[0] += 1ll * a[l] * b[l];
		return ;
	}
	int mid = (l + r) >> 1;
	int n = 1, L = 0;
	for(; n < r - l; n <<= 1, L++) ;
	for(int i = 0; i < n; ++i) {
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
	}
	//a[l..mid] -> b[mid + 1..r] || x < y || x + y
	for(int i = l; i <= mid; ++i) A[i - l].r = a[i];
	for(int i = mid + 1; i <= r; ++i) B[i - mid - 1].r = b[i];
	fft(A, n), fft(B, n);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i];
		w[i].i = -w[i].i;
	}
	fft(A, n);
	for(int i = 0; i < n; ++i) {
		ll tmp = (ll)(A[i].r / n + 0.5);
		f[i + l + mid + 1] += tmp;
		w[i].i = -w[i].i;
		A[i] = B[i] = C(0, 0);
	}
	for(int i = mid + 1; i <= r; ++i) A[i - mid - 1].r = a[i];
	for(int i = l; i <= mid; ++i) B[mid - i].r = b[i];
	fft(A, n), fft(B, n);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i];
		w[i].i = -w[i].i;
	}
	fft(A, n);
	for(int i = 0; i < n; ++i) {
		ll tmp = (ll)(A[i].r / n + 0.5);
		f[i + 1] += tmp;
		A[i] = B[i] = C(0,0);
	}
	work(l, mid), work(mid + 1, r);
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m, q;
		scanf("%d%d%d", &n, &m, &q);
		for(int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			a[x]++;
		}
		for(int i = 1, x; i <= m; ++i) {
			scanf("%d", &x);
			b[x]++;
		}
		work(0, 50000);
		for(int i = 1, x; i <= q; ++i) {
			scanf("%d", &x);
			printf("%lld\n", f[x]);
		}
		for(int i = 0; i <= 100000; ++i) {
			a[i] = b[i] = f[i] = 0;
		}
	}
	return 0;
}