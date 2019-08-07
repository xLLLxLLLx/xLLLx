#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N];
int nm[N][10];

int main() {
	int n ,m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", lx + 1);
		for(int j = 1; j <= m; ++j) {
			int pos = lx[j] - 'A' + 1;
			nm[j][pos]++;
		}
	}
	int ans = 0;
	for(int i = 1, x; i <= m; ++i) {
		int pos = 0;
		for(int j = 1; j <= 5; ++j)
			pos = max(pos, nm[i][j]);
		scanf("%d", &x);
		ans += x * pos;
	}
	printf("%d\n", ans);
	return 0;
}