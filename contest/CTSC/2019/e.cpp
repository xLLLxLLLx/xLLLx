#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2010, mod = 998244353;
int mx[N], to[N][30];
ll dp[N][N];
char lx[N];

ll mul(ll x, ll y) {
	return x * y % mod;
}

void Add(ll &x, ll y) {
	x = (x + y) % mod;
}

ll q_pow(ll x, int y) {
	ll ans = 1;
	for(; y; y >>= 1) {
		if(y & 1) ans = mul(ans, x);
		x = mul(x, x);
	}
	return ans;
}

int nxt[N], n, m;

void kmp() {
	int p = 0;
	for(int i = 2; i <= n; ++i) {
		if(lx[i] == lx[p + 1]) {
			nxt[i] = ++p;
			continue;
		}
		while(p && lx[i] != lx[p + 1]) {
			p = nxt[p];
			if(lx[i] == lx[p + 1]) {
				break;
			}
		}
		if(lx[i] == lx[p + 1]) {
			lx[i] = ++p;
		} else {
			nxt[i] = 0;
		}
	}
}

int main() {
	scanf("%d%s", &m, lx + 1);
	n = strlen(lx + 1);
	kmp();
	for(int i = 0; i <= n; ++i) {
		mx[i] = mx[nxt[i]];
		if(i + 1 <= n) mx[i] = max(mx[i], lx[i + 1] - 'a');
		for(int j = 0; j < mx[i]; ++j) to[i][j] = -1;
		for(int j = mx[i]; j < 26; ++j) {
			if(lx[i + 1] - 'a' == j) to[i][j] = i + 1;
			else {
				int p = nxt[i];
				while(p && to[nxt[p]][j] == -1) p = nxt[p];
				to[i][j] = to[p][j];
			}
		}
	}
	dp[0][0] = 1;
	for(int i = 0; i < m; ++i)
		for(int j = 0; j <= n; ++j) {
			if(!dp[i][j]) continue;
			for(int k = mx[j]; k < 26; ++k) {
				Add(dp[i + 1][to[j][k]], dp[i][j]);
			}
		}
	ll ans = 0;
	for(int i = 0; i <= n; ++i) {
		int p = i;
		for(int j = 0; j < m; ++j) {
			Add(ans, mul(25 - mx[p], dp[m - j - 1][i]));
			p = to[p][mx[p]];
		}
		if(p == i) Add(ans, 1);
	}
	printf("%lld\n", ((q_pow(26, m) - ans) % mod + mod) % mod);
	return 0;
}