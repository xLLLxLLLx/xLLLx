#include <bits/stdc++.h>
using namespace std;
const int N = 101, mod = 998244353;
int f[2][N][N][N];
struct data {
	int l, mx;
};
vector<data> a[N];

void Add(int &x, int y) {
	x = (x + y) % mod;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n, m;
		scanf("%d%d", &n, &m);
		for(int i = 0; i <= 1; ++i)
			for(int j = 0; j < n; ++j)
				for(int k = 0; k <= j; ++k)
					for(int t = 0; t <= k; ++t)
						f[i][j][k][t] = 0;
		for(int i = 1; i <= n; ++i)
			a[i].clear();
		for(int i = 1, l, r, x; i <= m; ++i) {
			scanf("%d%d%d", &l, &r, &x);
			a[r].push_back((data){l, x});
		}
		f[0][0][0][0] = 1;
		int now = 1;
		for(int i = 1; i <= n; ++i, now ^= 1) {
			for(int j = 0; j < i; ++j)
				for(int k = 0; k <= j; ++k)
					for(int t = 0; t <= k; ++t)
						f[now][j][k][t] = 0;
			for(int j = 0; j < i; ++j)
				for(int k = 0; k <= j; ++k)
					for(int t = 0; t <= k; ++t) {
						Add(f[now][j][k][t], f[now ^ 1][j][k][t]);
						Add(f[now][i - 1][j][k], f[now ^ 1][j][k][t]);
						Add(f[now][i - 1][k][t], f[now ^ 1][j][k][t]);
						Add(f[now][i - 1][j][t], f[now ^ 1][j][k][t]);
					}
			for(int g = 0; g < a[i].size(); ++g) {
				for(int j = 0; j < i; ++j)
					for(int k = 0; k <= j; ++k)
						for(int t = 0; t <= k; ++t) {
							if(1 + (a[i][g].l <= j) + (a[i][g].l <= k) + (a[i][g].l <= t) != a[i][g].mx)
								f[now][j][k][t] = 0;
						}
			}
			// for(int j = 0; j < i; ++j)
			// 	for(int k = 0; k <= j; ++k)
			// 		for(int t = 0; t <= k; ++t)
			// 			if(f[now][j][k][t]) printf("f[%d][%d][%d][%d][%d]= %d\n", i, j, k, t, f[now][j][k][t]);
		}
		int ans = 0;
		now = n & 1;
		for(int j = 0; j < n; ++j)
			for(int k = 0; k <= j; ++k)
				for(int t = 0; t <= k; ++t)
					Add(ans, f[now][j][k][t]);
		printf("%d\n", ans);
	}
	return 0;
}