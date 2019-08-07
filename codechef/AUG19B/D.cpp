#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			a[i] = 0;
		for(int i = 1, x; i <= n; ++i) {
			scanf("%d", &x);
			int l = max(1, i - x), r = min(n, i + x);
			a[l]++, a[r + 1]--;
		}
		for(int i = 1; i <= n; ++i)
			a[i] += a[i - 1];
		for(int i = 1; i <= n; ++i) 
			scanf("%d", &b[i]);
		sort(a + 1, a + 1 + n), sort(b + 1, b + 1 + n);
		int flg = 0;
		for(int i = 1; i <= n; ++i) {
			if(a[i] != b[i]) {
				flg = 1;
				printf("NO\n");
				break;
			}
		}
		if(!flg) 
			printf("YES\n");
	}
	return 0;
}