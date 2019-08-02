#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int a[N], qz[N][3][3], nm[N][3];
char lx[N];

int zh(char ch) {
	if(ch == 'R') return 0;
	if(ch == 'G') return 1;
	if(ch == 'B') return 2;
}

int main() {
	int q;
	scanf("%d", &q);
	for(int o = 1; o <= q; ++o) {
		int n, len;
		scanf("%d%d", &n, &len);
		scanf("%s", lx + 1);
		for(int i = 1; i <= n; ++i) {
			int pos = zh(lx[i]);
			for(int j = 0; j < 3; ++j)
				for(int k = 0; k < 3; ++k)
					qz[i][j][k] = qz[i - 1][j][k];
			for(int j = 0; j < 3; ++j)
				nm[i][j] = nm[i - 1][j];
			nm[i][i % 3]++;
			qz[i][i % 3][pos]++;
		}
		int ans = len;
		for(int i = 1; i <= n - len + 1; ++i)
			for(int j = 0; j < 3; ++j) {
				int r = i + len - 1, tmp = 0, k = i % 3, t = j;
				for(int g = 1; g <= 3; ++g) {
					tmp += (nm[r][k] - nm[i - 1][k]) - (qz[r][k][t] - qz[i - 1][k][t]);
					k = (k + 1) % 3, t = (t + 1) % 3;
				}
				ans = min(ans, tmp);
			}
		printf("%d\n", ans);
	}
	return 0;
}