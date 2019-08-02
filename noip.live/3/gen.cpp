#include <bits/stdc++.h>
using namespace std;

int main() {
	srand(time(NULL));
	int n = rand() % 8 + 1;
	printf("%d\n", n);
	for(int i = 1; i <= n; ++i) {
		int x = rand() % 5 + 1;
		printf("%d ", x);
	}
	puts("");
	for(int i = 1; i <= n; ++i) {
		int x = rand() % 5 + 1;
		printf("%d ", x);
	}
	return 0;
}