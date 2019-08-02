#include <bits/stdc++.h>
#define ll long long
using namespace std;
const ll mod = 1000000000000037;
const int N = 30, M = 5e6;
ll sum = 0, now = 0;
int n, cnt1 = 0, cnt2 = 0;
ll a[M], b[M];
char lx[N], ly[N], lz[N];

void Mul(ll &x, ll y) {
	x *= y;
	while(x >= mod) x -= mod;
}

void Add(ll &x, ll y) {
	x += y;
	while(x >= mod) x -= mod;
}

void dfs(int dep, int top) {
	if(dep == top + 1) {
		a[++cnt1] = now;
		return ;
	}
	ll pos = now;
	Mul(now, 127);
	Add(now, (int)lx[dep]);
	dfs(dep + 1, top);
	now = pos;
	Mul(now, 127);
	Add(now, (int)ly[dep]);
	dfs(dep + 1, top);
	now = pos;
	Mul(now, 127);
	Add(now, (int)lz[dep]);
	dfs(dep + 1, top);
}

void Dfs(int dep, int top) {
	if(dep == top + 1) {
		b[++cnt2] = now;
		return ;
	}
	ll pos = now;
	Mul(now, 127);
	Add(now, (int)lx[dep]);
	Dfs(dep + 1, top);
	now = pos;
	Mul(now, 127);
	Add(now, (int)ly[dep]);
	Dfs(dep + 1, top);
	now = pos;
	Mul(now, 127);
	Add(now, (int)lz[dep]);
	Dfs(dep + 1, top);
}

bool cmp(ll x, ll y) {
	return x > y;
}

int main() {
	scanf("%d", &n);
	scanf("%s%s%s", lx + 1, ly + 1, lz + 1);
	if(n == 1) {
		printf("%d\n", min((int)lx[1], min((int)ly[1], (int)lz[1])));
		return 0;
	}
	dfs(1, n / 2);
	now = 0;
	Dfs(n / 2 + 1, n);
	ll maxn = mod;
	for(int j = 1; j <= cnt1; ++j) 
		for(int i = n / 2 + 1; i <= n; ++i)
			a[j] = a[j] * 127 % mod;
	sort(b + 1, b + 1 + cnt2);
	sort(a + 1, a + 1 + cnt1, cmp);
	int dq = 1;
	for(int i = 1; i <= cnt1; ++i) {
		maxn = min(maxn, (a[i] + b[1]) % mod);
		ll gg = mod - a[i];
		while(dq < cnt2 && b[dq] < gg) dq++;
		maxn = min(maxn, (a[i] + b[dq]) % mod);
	}
	printf("%lld\n", maxn);
	return 0;
}