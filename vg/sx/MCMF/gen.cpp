#include <bits/stdc++.h>
using namespace std;

int main() {
	int T = rand() % 10 + 1;
	for(int o = 1; o <= T; ++o) {
		int n = rand() % 50 + 1, k = rand() % 10 + 1;
		printf("%d %d\n", n, k);
		for(int i = 1; i <= n; ++i){
			for(int j = 1; j <= n; ++j) {
				int x = rand() % 1001;
				printf("%d ", x);
			}
			puts("");
		}
	}
	return 0;
}