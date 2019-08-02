#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n;
		scanf("%d", &n);
		int minc = -1e5, maxc = 1e5, minr = -1e5, maxr = 1e5;
		int flg[5];
		memset(flg, 0, sizeof flg);
		for(int i = 1; i <= n; ++i) {
			int x, y, f1, f2, f3, f4;
			scanf("%d%d%d%d%d%d", &x, &y, &f1, &f2, &f3, &f4);
			if(!f3) {
				maxr = min(maxr, x);
				flg[1] = 1;
			}
			if(!f4) {
				minc = max(minc, y);
				flg[2] = 1;
			}
			if(!f1) {
				minr = max(minr, x);
				flg[3] = 1;
			}
			if(!f2) {
				maxc = min(maxc, y);
				flg[4] = 1;
			}
		}
		int x = 0, y = 0, F = 0;
		if(flg[1] || flg[3]) {
			if(flg[1]) x = maxr;
			if(flg[3]) x = minr;
			if(flg[1] && flg[3]) {
				if(maxr < minr) F = 1;
			}
		}
		if(flg[2] || flg[4]) {
			if(flg[2]) y = minc;
			if(flg[4]) y = maxc;
			if(flg[2] && flg[4]) {
				if(maxc < minc) F = 1;
			}
		}
		if(F) {
			printf("0\n");
		} else {
			printf("1 %d %d\n", x, y);
		}
	}
	return 0;
}