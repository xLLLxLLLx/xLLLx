#include <bits/stdc++.h>
using namespace std;
const int N = 25;
int a[N][N], maxn = 0;

void go(int x, int y) {
	int pos = 1;
	for(int i = 0; i < 4; ++i) {
		printf("%d ", a[x + i][y]);
		pos = pos * a[x + i][y];
	}
	puts("");
	maxn = max(maxn, pos);
}

void og(int x, int y) {
	int pos = 1;
	for(int i = 0; i < 4; ++i) {
		printf("%d ", a[x][y + i]);
		pos = pos * a[x][y + i];
	}
	puts("");
	maxn = max(maxn, pos);
}

void xz(int x, int y) {
	int pos = 1;
	for(int i = 0; i < 4; ++i) {
		printf("%d ", a[x + i][y + i]);
		pos = pos * a[x + i][y + i];
	}
	puts("");
	maxn = max(maxn, pos);
}

void zx(int x, int y) {
	int pos = 1;
	for(int i = 0; i < 4; ++i) {
		printf("%d ", a[x - i][y + i]);
		pos *= a[x - i][y + i];
	}
	puts("");
	maxn = max(maxn, pos);
}

int main() {
	for(int i = 1; i <= 20; ++i)
		for(int j = 1; j <= 20; ++j)
			scanf("%d", &a[i][j]);
	// int maxn = 0;
	for(int i = 1; i <= 20; ++i)
		for(int j = 1; j <= 20; ++j) {
			if(i + 3 <= 20) go(i, j);
			if(j + 3 <= 20) og(i, j);
			if(i + 3 <= 20 && j + 3 <= 20) xz(i, j);
			if(i > 3 && j + 3 <= 20) zx(i, j);
		}
	printf("%d\n", maxn);
	return 0;
}