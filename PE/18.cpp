#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int a[N][N], f[N][N];

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) 
		for(int j = 1; j <= i; ++j)
			scanf("%d", &a[i][j]);
	for(int i = 1; i <= n; ++i) f[n][i] = a[n][i];
	for(int i = n - 1; i >= 1; --i)
		for(int j = 1; j <= i; ++j) {
			f[i][j] = a[i][j] + max(f[i + 1][j], f[i + 1][j + 1]);
		}
	printf("%d\n", f[1][1]);
	return 0;
}