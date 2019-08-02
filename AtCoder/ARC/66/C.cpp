#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, mod = 1e9 + 7;
char lx[N];
int a[N];
ll f[N][3];

void Add(ll &x, ll y) {
	x = (x + y) % mod;
}

void Max(ll &x, ll y) {
	x = max(x, y);
}

ll add(ll x, ll y) {
	return (x + y) % mod;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		if(i != n) cin >> lx[i];
	}
	for(int i = 0; i <= n; ++i) 
		for(int j = 0; j < 3; ++j)
			f[i][j] = -1e18;
	f[1][0] = a[1];
	for(int i = 2; i <= n; ++i) {
		for(int j = 0; j < 3; ++j) {
			ll pos = a[i];
			int t = 0, now;
			if(lx[i - 1] == '-') t = 1;
			now = t ^ (j & 1);
			if(now) pos = -a[i];
			if(t && j < 2) Max(f[i][j + 1], f[i - 1][j] + pos);
			// printf("%d %d %lld\n", i, j, pos);
			for(int k = 0; k <= j; ++k) {
				Max(f[i][k], f[i - 1][j] + pos);
			}
		}
	}
	// for(int i = 1; i <= n; ++i)
	// 	for(int j = 0; j < 3; ++j) {
	// 		printf("f[%d][%d] = %lld\n", i, j, f[i][j]);
	// 	}
	printf("%lld\n", f[n][0]);
	return 0;
}