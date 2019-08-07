#include <bits/stdc++.h>
using namespace std;
const int N = 1010, mod = 1e9 + 7;
int dx[3] = {1, 1, 0};
int dy[3] = {1, 0, 1};
int nm[3];
int dp[2][3][N][N];

void Add(int &x, int y) {
	x += y;
	if(x > mod) x -= mod;
}

int main() {
	int n;
	cin >> n;
	for(int i = 0; i < 3; ++i)
		scanf("%d", &nm[i]);
	int now = 0;
	dp[0][0][1][1] = dp[0][1][1][0] = dp[0][2][0][1] = 1;
	for(int i = 2; i <= n; ++i) {
		now ^= 1;
		for(int t = 0; t < 3; ++t)
			for(int j = i / 2 - 1; j <= i; ++j)
				for(int k = i / 2 - 1; k <= i; ++k)
					dp[now][t][j][k] = 0;
		for(int t = 0; t < 3; ++t)
			for(int g = 0; g < 3; ++g) {
				if(g == t) continue;
				for(int j = i / 2 - 1; j <= i; ++j)
					for(int k = i / 2 - 1; k <= i; ++k) {
						int nj = j + dx[g], nk = k + dy[g];
						if(nj <= nm[0] && nk <= nm[1] && dp[now ^ 1][t][j][k]) {
							Add(dp[now][g][nj][nk], dp[now ^ 1][t][j][k]);
						}
					}
			}
	}
	int ans = 0;
	for(int i = 0; i < 3; ++i)
		ans = (ans + dp[now][i][nm[0]][nm[1]]) % mod;
	ans = 2ll * ans % mod;
	printf("%d\n", ans);
	return 0;
}