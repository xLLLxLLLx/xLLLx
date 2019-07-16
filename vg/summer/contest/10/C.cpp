#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], tr[N], dp[N], f[N];

int lower(int x) {
	return x & (-x);
}

void upd(int x, int y) {
	for(; x < N; x += lower(x)) tr[x] = max(tr[x], y);
}

int get(int x) {
	int ans = 0;
	for(; x; x -= lower(x)) ans = max(ans, tr[x]);
	return ans;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		a[x]++, a[y + 1]--;
	}
	for(int i = 1; i <= m; ++i) a[i] += a[i - 1];
	for(int i = 1; i <= m; ++i) a[i]++;
	dp[0] = 0;
	for(int i = 1; i <= m; ++i) {
		dp[i] = get(a[i]) + 1;
		upd(a[i], dp[i]);
	}
	int ans = 0;
	memset(tr, 0, sizeof tr);
	reverse(a + 1, a + 1 + m);
	f[0] = 0;
	for(int i = 1; i <= m; ++i) {
		f[i] = get(a[i]) + 1;
		upd(a[i], f[i]);
	}
	for(int i = 1; i <= m; ++i) {
		ans = max(ans, f[i] + dp[m - i + 1] - 1);
	}
	printf("%d\n", ans);
	return 0;
}