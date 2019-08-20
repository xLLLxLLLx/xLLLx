#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int ys[N];

int main() {
	int ans = 0, maxn = 10000;
	for(int i = 1; i <= maxn; ++i) {
		int len = sqrt(i), now = 1;
		for(int j = 2; j <= len; ++j) {
			if(i % j == 0) {
				now += j;
				if(j * j != i) now += i / j;
			}
		}
		if(now <= maxn) ys[i] = now;
	}
	for(int i = 1; i <= maxn; ++i) {
		if(ys[ys[i]] == i && i != ys[i]) {
			printf("%d %d\n", i, ys[i]);
			ans += i;
		}
	}
	printf("%d\n", ans);
	return 0;
}