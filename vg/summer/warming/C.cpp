#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
ll a[N][2], dp[N][2];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i][0]);
		dp[i][0] = a[i][0];
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%lld", &a[i][1]);
		dp[i][1] = a[i][1];
	}
	for(int i = 2; i <= n; ++i) 
	 for(int j = 0; j < 2; ++j) {
	 	dp[i][j] = max(dp[i][j], dp[i - 1][j ^ 1] + a[i][j]);
	 	dp[i][j] = max(dp[i][j], dp[i - 1][j]);
	}
	printf("%lld\n", max(dp[n][0], dp[n][1]));
	return 0;
}