#include <bits/stdc++.h>
using namespace std;
const double PI = acos(-1.0);
const int N = 2e6 + 10;
char lx[N];
struct C {
	double r, i;
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i * x.r); }
} a[N], d[N], w[N];
int c[N], f[N],v[N], base = 1000, lena = 0, lend = 0, cnt = 0;

void fft(C a[], int n) {
	for(int i = 0; i < n; ++i)
		if(rev[i] > i) 
			swap(a[i], a[rev[i]]);
	for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1) 
		for(int i = 0; i < n; i += (d << 1)) {
			for(int j = 0; j < d; ++j) {
				C tmp = w[t * j] * a[i + j + d];
				a[i + j + d] = a[i + j] - tmp;
				a[i + j] = a[i + j] + tmp;
			}
		}
}

int mult(C a[], C b[], int len) {
	int n = 1, L = 0;
	for(; n <= len; n <<= 1, L++) ;
	for(int i = 0; i < n; ++i) {
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (L - 1));
	}
	fft(a, n), fft(b, n);
	for(int i = 0; i < n; ++i) {
		a[i] = a[i] * b[i];
		w[i].i = -w[i].i;
	}
	fft(a, n);
	c[0] = 0;
	for(int i = 0; i < n; ++i) {
		c[i] += (int)(a[i].r + 0.5);
		c[i + 1] = c[i] / base;
		c[i] %= base;
	}
	while(!c[n] && n > 1) n--;
	return n;
}

void q_pow(C a[], int y) {
	for(; y; y >>= 1) {
		if(y & 1) {
			lend = mult(d, a, lena);
			for(int i = 0; i < lend; ++i) {
				d[i] = c[i];
			}
		}
		lena = mult(a, a, lena);
		for(int i = 0; i < lena; ++i) {
			a[i] = c[i];
		}
	}
}

bool judge(int x, int y) {
	if(x > y) return false;
	else if(x < y) return true;
	else {
		for(int i = x; i >= 0; --i) {
			if(v[i] < c[i]) return true;
			if(v[i] > c[i]) return false;
		}
	}
	return true;
}

bool check(int x, int y) {
	if(y) {
		for(int i = 0; i < lena; ++i) {
			a[i] = C(0, 0);
		}
		lena = 1;
		a[0].r = 3;
		q_pow(a, y);
		b[0].r = 1 << x;
		lend = mult(d, b);
	} else {
		lend = 0;
		c[0] = 1 << x;
	}
	return judge(cnt, lend);	
}

int main() {
	scanf("%s", lx);
	int len = strlen(lx);
	for(int i = 0; i < len; i += 4) {
		int h = 1;
		++cnt;
		for(int j = i; j < min(i + 3, len); ++j) {
			v[cnt] += h * (lx[j] - '0');
			h *= 10;
		}
	}
	int maxn = 1e9, pos = (int)(1.0 / log(3.0) * L);
	for(int i = 0; i <= 2; ++i) {
		for(int j = max(0, pos - 6); j <= pos + 6; ++j) {
			if(check(i, j)) {
				maxn = min(maxn, i * 2 + j * 3);
			}
		}
	}
	printf("%d\n", maxn);
	return 0;
}