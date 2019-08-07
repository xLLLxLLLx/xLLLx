#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int n, m, k, q;
ll dp[N][4];
int tr[N][4], id[N][4], c[N], mn[N], mx[N], L[N], R[N];

void Min(ll &x, ll y) {
	x = min(x, y);
}

int getl(int x) {
	int l = 1, r = q, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(c[mid] <= x) 
			ans = mid, l = mid + 1;
		else 
			r = mid - 1;
	}
	return c[ans];
}

int getr(int x) {
	int l = 1, r = q, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(c[mid] >= x)
			ans = mid, r = mid - 1;
		else
			l = mid + 1;
	}
	return c[ans];
}

int main() {
	scanf("%d%d%d%d", &n, &m, &k, &q);
	for(int i = 1; i <= n; ++i)
		mn[i] = 1e9;
	int maxn = 0;
	for(int i = 1, x, y; i <= k; ++i) {
		scanf("%d%d", &x, &y);
		maxn = max(maxn, x);
		mn[x] = min(mn[x], y);
		mx[x] = max(mx[x], y);
	}
	if(maxn == 1) {
		return printf("%d\n", mx[1] - 1), 0;
	}
	ll ans = maxn - 1;
	for(int i = 1, x; i <= q; ++i) {
		scanf("%d", &c[i]);
	}
	sort(c + 1, c + 1 + q);
	for(int i = 1; i <= m; ++i)
		L[i] = getl(i), R[i] = getr(i);
	for(int i = 1; i <= n; ++i) {
		if(mn[i] <= mx[i]) {
			ans += mx[i] - mn[i];	
			id[i][0] = L[mn[i]];
			id[i][1] = R[mn[i]];
			id[i][2] = L[mx[i]];
			id[i][3] = R[mx[i]];
		}
	}
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < 4; ++j)
			dp[i][j] = 1e18;
	//pre[1]
	if(mn[1] > mx[1]) {
		id[1][0] = R[1];
		dp[1][0] = id[1][0] - 1;
	} else {
		int tmp = mn[1] - 1;
		for(int i = 0; i < 4; ++i) {
			if(id[1][i]) Min(dp[1][i], tmp + abs(mx[1] - id[1][i]));
		}
	}
	for(int i = 2; i < maxn; ++i) {
		for(int j = 0; j < 4; ++j) {
			if(mn[i] > mx[i]) {
				id[i][j] = id[i - 1][j];
				dp[i][j] = dp[i - 1][j];
			} else if(dp[i - 1][j] == 1e18){
				continue;
			} else {
				int pos = id[i - 1][j];
				if(pos <= mn[i]) {
					int tmp = mn[i] - pos;
					for(int k = 0; k < 4; ++k) {
						if(id[i][k]) Min(dp[i][k], dp[i - 1][j] + tmp + abs(mx[i] - id[i][k]));
					}
				} else if(pos >= mx[i]) {
					int tmp = pos - mx[i];
					for(int k = 0; k < 4; ++k) {
						if(id[i][k]) Min(dp[i][k], dp[i - 1][j] + tmp + abs(mn[i] - id[i][k]));
					}
				} else {
					int tmp = pos - mn[i];
					for(int k = 2; k < 4; ++k) {
						if(id[i][k]) Min(dp[i][k], dp[i - 1][j] + tmp + abs(mx[i] - id[i][k]));
					}
					tmp = mx[i] - pos;
					for(int k = 0; k < 2; ++k) {
						if(id[i][k]) Min(dp[i][k], dp[i - 1][j] + tmp + abs(mn[i] - id[i][k]));
					}
				}
			}
		}
	}
	ll add = 1e18;
	for(int i = 0; i < 4; ++i) {
		int tmp = id[maxn - 1][i];
		if(!tmp || dp[maxn - 1][i] == 1e18) continue;
		ll pos = 1e18;
		if(tmp <= mn[maxn]) {
			Min(pos, mn[maxn] - tmp);
		} else if(tmp >= mx[maxn]) {
			Min(pos, tmp - mx[maxn]);
		} else {
			Min(pos, min(mx[maxn] - tmp, tmp - mn[maxn]));
		}
		Min(add, pos + dp[maxn - 1][i]);
	}
	ans += add;
	printf("%lld\n", ans);
	return 0;
}