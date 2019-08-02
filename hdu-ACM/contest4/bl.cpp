#include <bits/stdc++.h>
using namespace std;
const int N = 45;
int n, k, pos;
int a[N], b[N][N], num[N];

void dfs(int dep) {
	if(dep == n + 1) {
		for(int i = 1; i <= k; ++i) { 
			// printf("sum=%d\n", a[i]);
			for(int j = 1; j <= num[i]; ++j) {
				printf("%d ", b[i][j]);
			}
			puts("");
		}
		exit(0);
	}
	for(int i = 1; i <= k; ++i) {
		int flg = 0;
		if(a[i] + dep <= pos) {
			if(!a[i]) flg = 1;
			b[i][++num[i]] = dep;
			a[i] += dep;
			dfs(dep + 1);
			num[i]--, a[i] -= dep;
		}
		if(flg) break;
	}
}

int main() {
	scanf("%d%d", &n, &k);
	pos = n * (n + 1) / 2 / k;
	if(n * (n + 1) % (2 * k)) {
		return printf("No\n"), 0;
	}
	dfs(1);
	// printf("No\n");
	return 0;
}