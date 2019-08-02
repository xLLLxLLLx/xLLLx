#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int vs[N][N][N], A[N][N], B[N][N], C[N][N];
int na = 0, nb = 0, nc = 0;

void jl(int x, int y, int z) {
	if(!A[x][y]) na++;
	if(!B[x][z]) nb++;
	if(!C[y][z]) nc++;
	A[x][y] = B[x][z] = C[y][z] = 1;
}


int main() {
	int a, b, c;
	cin >> a >> b >> c;
	int tot = c * a * b;
	int d = max(a, max(b, c));
	if(tot / d < d) {
		puts("-1");
		exit(0);
	}
	int sum = a + b + c;
	if(d >= sum - d - 1) {
		printf("%d\n", d);
		if(a >= b && a >= c) {
			for(int i = 1; i <= b; ++i) {
				a--;
				printf("%d 1 1\n", i);
			}
			for(int i = 2; i <= c; ++i) {
				a--;
				printf("1 %d 1\n", i);
			}
			for(int i = 2; i <= b; ++i)
				for(int j = 2; j <= c; ++j) {
					if(a) {
						printf("%d %d 1\n", i, j);
						a--;
					}
				}
		}
		else if(b >= a && b >= c) {
			for(int i = 1; i <= a; ++i) {
				b--;
				printf("%d 1 1\n", i);
			}
			for(int i = 2; i <= c; ++i) {
				b--;
				printf("1 1 %d\n", i);
			}
			for(int i = 2; i <= c; ++i)
				for(int j = 2; j <= a; ++j) {
					if(b) {
						printf("%d 1 %d\n", j, i);
						b--;
					}
				}
		}
		else if(c >= a && c >= b) {
			for(int i = 1; i <= a; ++i) {
				c--;
				printf("1 %d 1\n", i);
			}
			for(int i = 2; i <= b; ++i) {
				c--;
				printf("1 1 %d\n", i);
			}
			for(int i = 2; i <= a; ++i)
				for(int j = 2; j <= b; ++j) {
					if(c) {
						c--;
						printf("1 %d %d\n", i, j);
					}
				}
		}
		return 0;
	}
	int x = d - c, y = d - b, z = d - a;
	int t = d - (x + y + z);
	if(t <= 0) {
		puts("-1");
		exit(0);
	}
	printf("%d\n", d);
	for(int i = 0; i < t; ++i) {
		printf("%d %d %d\n", i - 100, i - 100, i - 100);
	}
	for(int i = 1; i <= x; ++i) {
		printf("%d -100 -100\n", i - 100);
	}
	for(int i = 1; i <= y; ++i) {
		printf("-100 %d -100\n", i - 100);
	}
	for(int i = 1; i <= z; ++i) {
		printf("-100 -100 %d\n", i - 100);
	}
	return 0;
}