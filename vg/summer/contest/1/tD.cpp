#include <bits/stdc++.h>
#define ll long long
using namespace std;
const double PI = acos(-1.0);
const int N = 3e6 + 10;
char lx[N];
int base = 10000;
struct C {
	double r, i;
	C() {}
	C(double _r, double _i) { r = _r, i = _i; }
	C operator + (C x) { return C(r + x.r, i + x.i); }
	C operator - (C x) { return C(r - x.r, i - x.i); }
	C operator * (C x) { return C(r * x.r - i * x.i, r * x.i + i * x.r); }
} A[N], B[N], w[N];
int rev[N];
struct Big {
	int len;
	ll a[N];

	void clear() {
		for(int i = 1; i <= len; ++i) {
			a[i] = 0;
		}
		len = 0;
	}

	bool operator >= (Big &A) {
		if(len != A.len) {
			return len > A.len;
		}
		for(int i = len; i >= 1; --i) {
			if(a[i] != A.a[i]) {
				return a[i] > A.a[i];
			}
		}
		return 1;
	}

	void print() {
		printf("len=%d\n", len);
		for(int i = 1; i <= len; ++i) {
			printf("%04d ", a[i]);
		}
		puts("");
	}

	void bit() {
		for(int i = 1; i <= len; ++i) {
			a[i + 1] += a[i] / base;
			a[i] %= base;
		}
		while(a[len + 1]) {
			len++;
			a[len + 1] += a[len] / base;
			a[len] %= base;
		}
	}

	void operator *= (int x) {
		for(int i = 1; i <= len; ++i) {
			a[i] *= x;
		}
		bit();
	}

}n, x, tmp;

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

void mult(Big &a, Big &b, Big &c) {
	int n = 1, L = 0;
	for(; n < a.len + b.len; n <<= 1, L++) ;
	for(int i = 0; i < n; ++i) {
		w[i] = C(cos(2.0 * i * PI / n), sin(2.0 * i * PI / n));
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
		A[i] = C(0,0), B[i] = C(0, 0);
	}
	for(int i = 1; i <= a.len; ++i) {
		A[i - 1].r = a.a[i];
	}
	for(int i = 1; i <= b.len; ++i) {
		B[i - 1].r = b.a[i];
	}
	fft(A, n), fft(B, n);
	for(int i = 0; i < n; ++i) {
		A[i] = A[i] * B[i];
		w[i].i = -1.0 * w[i].i;
	}
	fft(A, n);
	c.clear();
	c.len = n;
	for(int i = 0; i < n; ++i) {
		c.a[i + 1] = (ll)(A[i].r / n + 0.5);
	}
	while(!c.a[c.len] && c.len > 1) c.len--;
	c.bit();
}

void q_pow(int y) {
	if(!y) {
		x.clear();
		x.len = 1;
		x.a[1] = 1;
		return ;
	}
	q_pow(y >> 1);
	mult(x, x, x);
	if(y & 1) {
		x *= 3;
	}
}

int pw[4] = {1, 10, 100, 1000};

bool check(Big &x, int y) {
	tmp = x;
	tmp *= y;
	if(tmp >= n) {
		return true;
	} else return false;
}

int main() {
	scanf("%s", lx + 1);
	n.len = strlen(lx + 1);
	int pos = max((int)(log(10.0) / log(3.0) * n.len) - 3, 0);
	for(int i = 1; i <= n.len; ++i) {
		n.a[(n.len - i) / 4 + 1] += (lx[i] - '0') * pw[(n.len - i) % 4];
	}
	n.len = (n.len - 1) / 4 + 1;
	if(n.len == 1 && n.a[1] == 1) {
		return printf("1\n"), 0;
	}
	q_pow(pos);
	for(; ; ) {
		for(int i = 2; i <= 4; ++i) {
			if(check(x, i)) {
				// printf("%d %d\n", pos, i);
				return printf("%d\n", pos * 3 + i), 0;
			}
		}
		pos++;
		x *= 3;
	}
	return 0;
}