#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 12, M = (1 << 11) + 10;
int chk[M];
ll dp[N][M];

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) == 2 && (n || m)) {
		memset(dp, 0, sizeof dp);
		int len = (1 << m);
		dp[1][0] = 1;
		for(int i = 0; i < len; ++i) {
			chk[i] = 1;
			for(int j = 0; j < m; ++j) {
				if((i >> j) & 1) continue;
				if(j + 1 == k || (i >> (j + 1)) & 1) chk[i] = 0;
				else j++;
			}
		}
		for(int i = 1; i <= n; ++i) 
			for(int j = 0; j < len; ++j) {
				if(!dp[i][j]) continue;
				dp[i + 1][len ^ j] += dp[i][j];
				if(chk[len ^ j]) {
					dp[i + 1][j] += dp[i][j];
					dp[i][len - 1] += dp[i][j];
				}
			}
		for(int i = 1; i <= n; ++i)
			for(int j = 0; j < len; ++j)
				printf("dp[%d][%d]=%lld\n", i, j, dp[i][j]);
		printf("%lld\n", dp[n][len - 1]);
	}
	return 0;
}