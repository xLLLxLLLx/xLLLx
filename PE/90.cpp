#include <bits/stdc++.h>
using namespace std;
const int N = 10, M = 1010;
int a[M][N], b[N], nx[N], ny[N], res = 0;

void dfs(int dep, int lst) {
	if(dep > 6) {
		++res;
		for(int i = 1; i <= 6; ++i)
			a[res][i] = b[i];
		return ;
	}
	for(int i = lst + 1; i <= 9; ++i) {
		b[dep] = i;
		dfs(dep + 1, i);
	}
}

int sx[10] = {0, 0, 0, 1, 2, 3, 4, 6, 8};
int sy[10] = {1, 4, 9, 6, 5, 6, 9, 4, 1};

bool check(int x, int y) {
	memset(nx, 0, sizeof nx);
	memset(ny, 0, sizeof ny);
	for(int i = 1; i <= 6; ++i) {
		nx[a[x][i]] = 1;
		if(a[x][i] == 6) nx[9] = 1;
		if(a[x][i] == 9) nx[6] = 1;
	}
	for(int i = 1; i <= 6; ++i) {
		ny[a[y][i]] = 1;
		if(a[y][i] == 6) ny[9] = 1;
		if(a[y][i] == 9) ny[6] = 1;
	}
	for(int i = 0; i < 9; ++i) {
		int flg = 0;
		if(nx[sx[i]] && ny[sy[i]]) flg = 1;
		if(nx[sy[i]] && ny[sx[i]]) flg = 1;
		if(!flg) return false;
	}
	return true;
}

int main() {
	dfs(1, -1);
	int ans = 0;
	for(int i = 1; i <= res; ++i)
		for(int j = i; j <= res; ++j) {
			ans += check(i, j);
		}
	printf("%d\n", ans);
	return 0;
}