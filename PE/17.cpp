#include <bits/stdc++.h>
using namespace std;
int a[12], b[12], c[12];

int main() {
	int ans = 11;
	a[0] = 0, a[1] = a[2] = a[6] = 3, a[4] = a[5] = a[9] = 4, a[3] = a[7] = a[8] = 5;
	b[0] = 3, b[1] = 6, b[2] = 6, b[3] = 8, b[4] = 8, b[5] = 7, b[6] = 7, b[7] = 9, b[8] = 8, b[9] = 8;
	c[0] = 0, c[4] = c[5] = c[6] = 5, c[2] = c[3] = c[8] = c[9] = 6, c[7] = 7;
	for(int i = 0; i <= 9; ++i)
		for(int j = 0; j <= 9; ++j)
			for(int k = 0; k <= 9; ++k) {
				int res = 0;
				if(!i) {
					if(j == 1) {
						res += b[k];
					} else res += c[j] + a[k];
				} else {
					res += a[i] + 7;
					if(j || k) {
						res += 3;
						if(j == 1) res += b[k];
							else res += c[j] + a[k];
					}
				}
				ans += res;
				if(i) {
					printf("%d%d%d", i, j, k);
				} else if(j) {
					printf("%d%d", j, k);
				} else {
					printf("%d", k);
				}
				printf("\nres=%d\n", res);
			}
	printf("%d\n", ans);
	return 0;
}