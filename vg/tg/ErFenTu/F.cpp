#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int M = (1 << 21) + 10;
int xv[M], yv[M];
int x[M], y[M], cnt[M];
int xe[M], ye[M], xb[M], yb[M];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j) {
			int x;
			scanf("%1d", &x);
			if(x) {
				xe[1 << i] |= (1 << j), ye[1 << j] |= (1 << i);
			}
		}
	for(int i = 0; i < n; ++i)
		scanf("%d", &xv[i]);
	for(int i = 0; i < m; ++i)
		scanf("%d", &yv[i]);
	int t;
	scanf("%d", &t);
	for(int i = 0; i < M; ++i)
		cnt[i] = cnt[i >> 1] + (i & 1);
	int xtot = 0, ytot = 0, len = (1 << n);
	for(int i = 0; i < len; ++i) {
		xb[i] = 1;
		int sum = 0;
		for(int j = 0; j < n; ++j) {
			if((i >> j) & 1) {
				xb[i] &= xb[i ^ (1 << j)]; 
				xe[i] |= xe[i ^ (1 << j)];
				sum += xv[j];
			}
		}
		xb[i] &= (cnt[i] <= cnt[xe[i]]);
		if(xb[i])
			x[++x[0]] = sum;
	}
	len = (1 << m);
	for(int i = 0; i < len; ++i) {
		yb[i] = 1;
		int sum = 0;
		for(int j = 0; j < m; ++j) {
			if((i >> j) & 1) {
				yb[i] &= yb[i ^ (1 << j)]; 
				ye[i] |= ye[i ^ (1 << j)];
				sum += yv[j];
			}
		}
		yb[i] &= (cnt[i] <= cnt[ye[i]]);
		if(yb[i])
			y[++y[0]] = sum;
	}
	sort(x + 1, x + x[0] + 1);
	// for(int i = 1; i <= x[0]; ++i)
	// 	printf("x[%d]=%d\n", i, x[i]);
	// for(int i = 1; i <= y[0]; ++i)
	// 	printf("y[%d]=%d\n", i, y[i]);
	ll ans = 0;
	for(int i = 1; i <= y[0]; ++i) {
		ans += x[0] - (lower_bound(x + 1, x + 1 + x[0], t - y[i]) - x) + 1;
	}
	printf("%lld\n", ans);
	return 0;
}