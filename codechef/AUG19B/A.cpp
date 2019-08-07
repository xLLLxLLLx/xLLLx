#include <bits/stdc++.h>
using namespace std;
const int N = 210;
int a[N], b[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		int maxn = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &b[i]);
			maxn = max(maxn, a[i] * 20 - b[i] * 10);
		}
		printf("%d\n", maxn);
	}
}