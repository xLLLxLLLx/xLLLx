#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int a[N], dp[N][N];

void Max(int &x, int y) {
	x = max(x, y);
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
	}
	for(int len = 2; len <= n; ++len) {
		for(int l = 1; l <= n - len + 1; ++l) {
			int r = l + len - 1;
			for(int k = l + 1; k <= r - 1; ++k)
				Max(dp[l][r], dp[l][k] + dp[k][r] + a[l] * a[r]);
		}
	}
	printf("%d\n", dp[1][n]);
	return 0;
}