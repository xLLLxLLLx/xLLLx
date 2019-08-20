#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int nm[N];

int gcd(int a, int b) {
	return b ? gcd(b, a % b) : a;
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		for(int j = i; j <= n; ++j) {
			int x = i + j, y = i * j;
			int gg = gcd(x, y);
			if(x == gg) {
				nm[y / gg]++;
				// if(y / gg == 6) printf("%d %d %d\n", i, j, y / gg);
			}
		}
	}
	int maxn = 0;
	for(int i = 1; i <= n; ++i) {
		maxn = max(maxn, nm[i]);
		if(nm[i] >= 1000) {
			printf("%d\n", i);
		}
	}
	printf("maxn%d\n", maxn);
	return 0;
}