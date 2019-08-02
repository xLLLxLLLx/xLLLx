#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		a[x]++;
	}
	int pos = n / 2 + (n & 1), res = 0, ans = 0;
	for(int i = 1; i <= k; ++i) {
		pos -= a[i] / 2;
		ans += a[i] / 2 * 2;
		res += a[i] & 1;
	}
	ans += min(pos, res);
	printf("%d\n", ans);
	return 0;
}