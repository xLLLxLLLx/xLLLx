#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, w, q;
		scanf("%d%d%d", &n, &w, &q);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		int now = 0, last = 0;
		for(int i = 1; i <= n; ++i) {
			i = max(i, last);
			for(; last <= n && a[last] + now <= w; ++last)
				now += a[last] + 1;
		}
	}
	return 0;
}