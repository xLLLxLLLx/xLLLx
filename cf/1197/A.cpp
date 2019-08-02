#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		sort(a + 1, a + 1 + n);
		int ans = min(n - 2, a[n - 1] - 1);
		printf("%d\n", ans);
	}
	return 0;
}