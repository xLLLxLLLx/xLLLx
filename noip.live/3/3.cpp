#include <bits/stdc++.h>
using namespace std;
const int N = 51;
double dp[2][N][N][N], sum[2];

double get(int id, int r, int g, int b, int mr, int mg, int mb) {
	if(r < mr || g < mg || b < mb) {
		return 0;
	}
	double ans = dp[id][r][g][b] - dp[id][r][g][mb - 1] - dp[id][r][mg - 1][b] - dp[id][mr - 1][g][b]
								+ dp[id][mr - 1][mg - 1][b] + dp[id][mr - 1][g][mb - 1] + dp[id][r][mg - 1][mb - 1]
								- dp[id][mr - 1][mg - 1][mb - 1];
	return ans;
}

void init(int id) {
	for(int i = 0; i < N; ++i)
		for(int j = 0; j < N; ++j)
			for(int k = 0; k < N; ++k)
				dp[id][i][j][k] = 0;
}

void upd(int id) {
	for(int i = 1; i < N; ++i)
		for(int j = 1; j < N; ++j)
			for(int k = 1; k < N; ++k) {
				dp[id][i][j][k] += dp[id][i - 1][j][k] + dp[id][i][j - 1][k] + dp[id][i][j][k - 1] - dp[id][i - 1][j - 1][k] - dp[id][i - 1][j][k - 1] - dp[id][i][j - 1][k - 1] + dp[id][i - 1][j - 1][k - 1];
			}
}

int count(int r, int g, int b, int mr, int mg, int mb) {
	if(r < mr || g < mg || b < mb) return 0;
	int res = (r - mr + 1);
	res *= (g - mg + 1);
	res *= (b - mb + 1);
	return res;
}

int main() {
	int n, R, G, B, r, g, b, d1, d2;
	cin >> n >> R >> G >> B >> r >> g >> b >> d1 >> d2;
	r++, g++, b++;
	int now = 0;
	int tmp = count(min(R, r + d2), min(G, g + d2), min(B, b + d2), max(1, r - d2), max(1, g - d2), max(1, b - d2)) - count(min(R, r + d1 - 1), min(G, g + d1 - 1), min(B, b + d1 - 1), max(1, r - d1 + 1), max(1, g - d1 + 1), max(1, b - d1 + 1));
	dp[now][r][g][b] = 1.0 / tmp;
	upd(now);
	for(int i = 1; i <= n; ++i) {
		now ^= 1;
		init(now);
		for(int j = 1; j <= R; ++j)
			for(int k = 1; k <= G; ++k)
				for(int t = 1; t <= B; ++t) {
					dp[now][j][k][t] = get(now ^ 1, min(R, j + d2), min(G, k + d2), min(B, t + d2), max(1, j - d2), max(1, k - d2), max(1, t - d2));
					dp[now][j][k][t] -= get(now ^ 1, min(R, j + d1 - 1), min(G, k + d1 - 1), min(B, t + d1 - 1), max(1, j - d1 + 1), max(1, k - d1 + 1), max(1, t - d1 + 1));
					if(dp[now][j][k][t] < 0) {
						dp[now][j][k][t] = 0;
					}
				}
		if(i <= n - 2) {
			for(int j = 1; j <= R; ++j)
				for(int k = 1; k <= G; ++k)
					for(int t = 1; t <= B; ++t) {
						int pos = count(min(R, j + d2), min(G, k + d2), min(B, t + d2), max(1, j - d2), max(1, k - d2), max(1, t - d2)) - count(min(R, j + d1 - 1), min(G, k + d1 - 1), min(B, t + d1 - 1), max(1, j - d1 + 1), max(1, k - d1 + 1), max(1, t - d1 + 1));
						if(pos) 
							dp[now][j][k][t] /= pos;
						else dp[now][j][k][t] = 0;
					}
		}
		if(i != n)
			upd(now);
	}
	printf("%.12f\n", 1.0 - dp[now][r][g][b]);
	return 0;
}