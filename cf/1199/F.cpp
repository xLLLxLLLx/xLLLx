#include <bits/stdc++.h>
using namespace std;
const int N = 55;
char lx[N][N];
int dp[N][N][N][N];

int dfs(int L, int R, int l, int r) {
	if(~dp[L][R][l][r]) 
		return dp[L][R][l][r];
	if(L == R && l == r) {
		return lx[L][l] == '#';
	}
	int ans = max(R - L + 1, r - l + 1);
	for(int i = L; i < R; ++i) 
		ans = min(ans, dfs(L, i, l, r) + dfs(i + 1, R, l, r));
	for(int i = l; i < r; ++i)
		ans = min(ans, dfs(L, R, l, i) + dfs(L, R, i + 1, r));
	return dp[L][R][l][r] = ans;
}

int main() {
	memset(dp, -1, sizeof dp);
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", lx[i] + 1);
	}
	printf("%d\n", dfs(1, n, 1, n));
	return 0;
}