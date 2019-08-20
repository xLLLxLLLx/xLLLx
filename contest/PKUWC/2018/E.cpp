#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
const int N = (1 << 20) + 1, LOG = 30;

void read(int &x) {
	char ch = getchar(); x = 0;
	for(; ch < '0' || ch > '9'; ch = getchar()) ;
	for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

int mul(int x, int y) {
	return 1ll * x * y % mod;
}

int add(int x, int y) {
	return (x + y) % mod;
}

void Add(int &x, int y) {
	x = (x + y) % mod;
}

void Mul(int &x, int y) {
	x = mul(x, y);
}

int q_pow(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

int A[LOG][N], deg[LOG], g[N], w[N], rev[N];

void ntt(int a[N], int n) {
  for(int i = 0; i < n; ++i) 
    if(rev[i] > i)
      swap(a[i], a[rev[i]]);
  for(int t = n >> 1, d = 1; d < n; t >>= 1, d <<= 1)
    for(int i = 0; i < n; i += (d << 1))
      for(int j = 0; j < d; ++j) {
        int tmp = mul(g[t * j], a[i + j + d]);
        a[i + j + d] = (a[i + j] - tmp + mod) % mod;
        a[i + j] = (a[i + j] + tmp) % mod;
      }
}

void goNTT(int a[N], int b[N], int n, int L) {
  for(int i = 0; i < n; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
  }
  g[0] = 1, g[1] = q_pow(3, (mod - 1) / n);
  for(int i = 2; i < n; ++i) {
    g[i] = mul(g[i - 1], g[1]);
  }
  ntt(a, n), ntt(b, n);
  for(int i = 0; i < n; ++i) {
    a[i] = mul(a[i], b[i]);
  }
  g[1] = q_pow(g[1], mod - 2);
  for(int i = 2; i < n; ++i) {
    g[i] = mul(g[i - 1], g[1]);
  }
  ntt(a, n);
  int pos = q_pow(n, mod - 2);
  for(int i = 0; i < n; ++i) {
    a[i] = mul(a[i], pos);
  }
}

int cnt = 0;

void work(int l, int r) {
	if(l == r) {
		++cnt;
		deg[cnt] = w[l];
		A[cnt][0] = 1, A[cnt][w[l]] = -1;
		for(int i = 1; i < w[l]; ++i) A[cnt][i] = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	work(l, mid), work(mid + 1, r);
	int n = 1, L = 0, na = cnt - 1, nb = cnt, m = deg[na] + deg[nb];
	for(; n <= m; n <<= 1, L++);
	for(int i = deg[na] + 1; i < n; ++i) A[na][i] = 0;
	for(int i = deg[nb] + 1; i < n; ++i) A[nb][i] = 0;
	goNTT(A[na], A[nb], n, L);
	deg[--cnt] = m;
}

int main() {
	// freopen("in", "r", stdin);
	int n, sum = 0;
	A[0][1] = 1;
	read(n);
	for(int i = 1; i <= n; ++i) {
		read(w[i]);
		if(i > 1) sum += w[i];
	}
	work(2, n);
	int ans = 0;
	// printf("cnt=%d\n", cnt);
	// for(int i = 0; i <= sum; ++i) {
	// 	printf("%d ", A[1][i]);
	// }
	for(int i = 0; i <= sum; ++i) {
		Add(ans, mul(A[1][i], mul(w[1], q_pow(i + w[1], mod - 2))));
	}
	ans = (ans + mod) % mod;
	printf("%d\n", ans);
	return 0;
}