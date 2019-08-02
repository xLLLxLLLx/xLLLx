#include <bits/stdc++.h>
using namespace std;
const int inf = 1e9;

int main() {
	int n = rand() % 100 +1;
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i) {
		int num = rand() % 1000 + 3;
		printf("%d\n", num);
		for(int j = 1; j <= num; ++j) {
			int x = rand() % (2 * inf) - inf, y = rand() % (2 * inf) - inf;
			printf("%d %d\n", x, y);
		}
	}
	int q = rand() % 10 + 1;
	printf("%d\n", q);
	for(int i = 1; i <= q; ++i) {
		int x = rand() % n + 1, y = rand() % n + 1;
		if(x > y) swap(x, y);
		printf("%d %d\n", x, y);
	}
	return 0;
}