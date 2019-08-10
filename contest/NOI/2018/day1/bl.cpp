#include <bits/stdc++.h>
using namespace std;
const int N = 40010;
char lx[N], s[N];

int main() {
	scanf("%s", lx + 1);
	int n = strlen(lx + 1);
	int T;
	scanf("%d", &T);
	for(int o = 1, l, r; o <= T; ++o) {
		scanf("%s%d%d", s + 1, &l, &r);
		int len = strlen(s + 1);
		ll ans = 0;
		for(int i = 1; i <= len; ++i) {
			
			for(int j = 1; j <= n; ++j) {

			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}