#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
int a[N], mx[N], my[N], vis[N], w[N];
ll f[N];

int main() {
	int n, q, t;
	scanf("%d%d%d", &n, &q, &t);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int i = 1, x, y; i <= q; ++i) {
		scanf("%d%d", &x, &y);
		mx[x] = y, my[y] = x;
	}
	for(int i = 1; i <= n; ++i) {
		if(!my[i]) {
			// printf("qwq%d\n", i);
			int tmp = i, pos = a[tmp];
			w[tmp] = pos;
			while(mx[tmp]) {
				t -= pos;
				if(t < 0) return printf("0\n"), 0;
				tmp = mx[tmp];
				pos += a[tmp];
				w[tmp] = pos;
			}
		}
	}
	f[0] = 1;
	for(int i = 1; i <= n; ++i) {
		if(!w[i]) return printf("0\n"), 0;
		for(int j = w[i]; j <= t; ++j) {
			f[j] = (f[j] + f[j - w[i]]) % mod;
		}
	}
	// printf("%d\n", t);
	if(t >= 0) printf("%lld\n", f[t]);
	else {
		printf("0\n");
	}
	return 0;
}