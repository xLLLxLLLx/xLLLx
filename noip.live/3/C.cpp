#include <bits/stdc++.h>
using namespace std;
const int N = 51;
long double tr[2][N][N][N], dp[2][N][N][N];

int lower(int x) {
	return x & (-x);
}

void change(int x, int y, int z, long double w, int id) {
	for(int i = x; i < N; i += lower(i))
		for(int j = y; j < N; j += lower(j))
			for(int k = z; k < N; k += lower(k))
				tr[id][i][j][k] += w;
}

long double get(int x, int y, int z, int id) {
	long double ans = 0;
	for(int i = x; i; i -= lower(i))
		for(int j = y; j; j -= lower(j))
			for(int k = z; k; k -= lower(k))
				ans += tr[id][i][j][k];
	return ans;
}

int main() {
	int n, R, G, B, r, g, b, d1, d2;
	cin >> n >> R >> G >> B >> r >> g >> b >> d2 >> d1;
	r++, g++, b++;
	int now = 0;
	change(r, g, b, 1, now);
	for(int i = 1; i <= n; ++i) {
		now ^= 1;
		for(int j = 1; j <= R; ++j)
			for(int k = 1; k <= G; ++k)
				for(int t = 1; t <= B; ++t)
					tr[now][j][k][t] = 0;
		for(int j = 1; j <= R; ++j)
			for(int k = 1; k <= G; ++k)
				for(int t = 1; t <= B; ++t) {
					long double pos = get(min(j + d1, R), min(k + d1, G), min(t + d1, B), now ^ 1) - get(max(1, j - d1) - 1, max(1, k - d1) - 1, max(1, t - d1) - 1, now ^ 1);
					long double tmp = get(min(j + d2, R), min(k + d2, G), min(t + d2, B), now ^ 1) - get(max(1, j - d2) - 1, max(1, k - d2) - 1, max(1, t - d2) - 1, now ^ 1);
					dp[now][j][k][t] = pos - tmp;
					change(j, k, t, dp[now][j][k][t], now);
					printf("dp[%d][%d][%d][%d]=%lf\n", i, j, k, t, dp[now][j][k][t]);
				}
	}
	long double sum = 0;
	for(int i = 1; i <= R; ++i)
		for(int j = 1; j <= G; ++j)
			for(int t = 1; t <= B; ++t)
				sum += dp[now][i][j][t];
	long double pos = get(min(r + d1, R), min(g + d1, G), min(b + d1, B), now) - get(max(1, r - d1) - 1, max(1, g - d1) - 1, max(1, b - d1) - 1, now);
	long double tmp = get(min(r + d2, R), min(g + d2, G), min(b + d2, B), now) - get(max(1, r - d2) - 1, max(1, g - d2) - 1, max(1, b - d2) - 1, now);
	long double ans = (sum - (pos - tmp));
	printf("%.10f\n", ans / sum);
	return 0;
}