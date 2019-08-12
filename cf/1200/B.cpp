#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int a[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m, k;
		scanf("%d%d%d", &n, &m, &k);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a[i]);
		}
		int flg = 1;
		for(int i = 1; i < n; ++i) {
			if(a[i] + m + k < a[i + 1]) {
				flg = 0;
				break;
			}
			int res = max(0, a[i + 1] - k);
			if(a[i] <= res) {
				m -= res - a[i];
			} else {
				m += a[i] - res;
			}
		}
		if(flg) puts("YES");
		else puts("NO");
	}
	return 0;
}