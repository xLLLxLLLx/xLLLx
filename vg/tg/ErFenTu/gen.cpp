#include <bits/stdc++.h>
using namespace std;
const int inf = 1e6, INF = 4e8;

int main() {
	srand(time(NULL));
	int n = rand() % 10 + 1, m = rand() % 10 +1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			int x = rand() % 2;
			printf("%d", x);
		}
		puts("");
	}
	for(int i = 1; i <= n; ++i) {
		int x = rand() % inf + 1;
		printf("%d ", x);
	}
	puts("");
	for(int i = 1; i <= m; ++i) {
		int x = rand() % inf + 1;
		printf("%d ", x);
	}
	puts("");
	int x = rand() % INF + 1;
	printf("%d\n", x);
	return 0;
}