#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110;
struct data {
	int nt, to;
} a[N << 1];
int head[N], cnt = 0;
ll dp[N][N][N];

void add(int x, int y) {
	a[++cnt].to = y;
	a[cnt].nt = head[x];
	head[x] = cnt;
}

void dfs(int u, int fa) {
	for(int i = head[u]; i; i = a[i].nt) {
		int to = a[i].to;
		if(to == fa) {
			continue;
		}
		dfs(to, u);
		for(
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1, x, y; i < n; ++i) {
		scanf("%d%d", &x, &y);
		add(x, y), add(y, x);
	}
	dfs(1, 0);
	ll tot = 1ll << (n - 1);
	double ans = 0;
	for(int i = 0; i <= 100; ++i)
		for(int j = 0; j <= 100; ++j) {
			ans += (double)dp[1][i][j] / double(tot);
		}
	printf("%.10f\n", ans);
	return 0;
}