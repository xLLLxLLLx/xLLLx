#include <bits/stdc++.h>
using namespace std;
const int N = 25, mod = 1e9 + 7;
int jc[N] = {1}, ny[N] = {1}, bx[N], by[N];
struct data {
	int x, y;
} a[N];

int add(int x, int y) {
	return (x += y) > mod ? x - mod : x;
}

int sub(int x, int y) {
	return (x -= y) < 0 ? x + mod : x;
}

int mul(int x, int y) {
	return (long long)x * y % mod;
}

int q_pow(int x, int y) {
	int ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) 
			ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

void init() {
	for(int i = 1; i < N; ++i)
		jc[i] = mul(jc[i - 1], i), ny[i] = q_pow(jc[i], mod - 2);
}

int C(int x, int y) {
	return mul(jc[x], mul(ny[y], ny[x - y]));
}

int A(int x, int y) {
	return mul(C(x, y), jc[y]);
}

int main() {
	init();
	int n, m;
	scanf("%d%d", &n, &m);
	int mx = max(n, m), mn = min(n, m);
	int cnt = 0;
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= m; ++j) {
			char ch;
			cin >> ch;
			if(ch == 'B')
				a[++cnt] = (data){i, j};
		}
	int len = (1 << cnt), ans = 0;
	for(int i = 0; i < len; ++i) {
		memset(bx, 0, sizeof bx);
		memset(by, 0, sizeof by);
		int res = 0, flg = 0;
		for(int j = 0; j < cnt; ++j) {
			if((i >> j) & 1) {
				res++;
				if(bx[a[j + 1].x] || by[a[j + 1].y]) {
					flg += bx[a[j + 1].x] + by[a[j + 1].y];
				}
				bx[a[j + 1].x] = by[a[j + 1].y] = 1;
			}
		}
		if(res + flg > mn) 
			continue;
		int tmp = mul(jc[mn - flg], A(mx - res, mn - res - flg));
		printf("%d %d\n", i, tmp);
		if(res & 1)
			ans = sub(ans, tmp);
		else 
			ans = add(ans, tmp);
	}
	printf("%d\n", ans);
	return 0;
}