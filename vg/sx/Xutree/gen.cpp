#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	for(int o = 1; o <= 4; ++o) {
		int n = rand() % 10 + 2;
		printf("%d\n", n);
		for(int i = 1; i <= n; ++i) {
			int x = rand() % n + 1;
			printf("%d ", x);
		}
		puts("");
		for(int i = 2; i <= n; ++i) {
			int y = rand() % (i - 1) + 1;
			printf("%d %d\n", i, y);
		}
	}
	return 0;
}