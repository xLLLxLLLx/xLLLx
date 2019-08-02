#include <bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1
using namespace std;

int main() {
	srand(time(NULL));
	int T = 2, pos = (1 << 30) - 1;
	printf("10\n");
	for(int o = 1; o <= 10; ++o) {
		int n = 100000, m = 100000;
		printf("%d %d\n", n, m);
		for(int i = 1; i <= n; ++i) {
			int x = rand() % pos;
			printf("%d\n", x);
		}
		for(int i = 1; i <= m; ++i) {
			int op = rand() % 2;
			if(op == 1) {
				int x = rand() % pos;
				printf("%d %d\n", op, x);
			} else {
				int l = rand() % pos, r = rand() % pos;
				printf("%d %d %d\n", op, l, r);
			}
		}
	}
	return 0;
}