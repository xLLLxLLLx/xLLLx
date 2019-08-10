#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int mx[N][2], mn[N][2];
set<int> sx, sy;
char lx[N];

int zh(char ch) {
	if(ch == 'D') return 1;
	if(ch == 'W') return 0;
	if(ch == 'S') return 2;
	if(ch == 'A') return 3;
}

int hz(char ch) {
	if(ch == 'A') return 1;
	if(ch == 'S') return 0;
	if(ch == 'W') return 2;
	if(ch == 'D') return 3;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		sx.clear(), sy.clear();
		scanf("%s", lx + 1);
		int n = strlen(lx + 1);
		int x = 0, y = 0;
		mx[0][0] = mn[0][0] = mx[0][1] = mn[0][1] = 0;
		sx.insert(0), sy.insert(0);
		for(int i = 1; i <= n; ++i) {
			int z = zh(lx[i]);
			x += dx[z], y += dy[z];
			sx.insert(x), sy.insert(y);
			mx[i][0] = *sx.rbegin(), mn[i][0] = *sx.begin();
			mx[i][1] = *sy.rbegin(), mn[i][1] = *sy.begin();
		}
		// for(int i = 1; i <= n; ++i) {
		// 	for(int j = 0; j < 2; ++j) {
		// 		printf("mx[%d][%d] = %d\n", i, j, mx[i][j]);
		// 		printf("mn[%d][%d] = %d\n", i, j, mn[i][j]);
		// 	}
		// }
		ll maxn = 1ll * (mx[n][0] - mn[n][0] + 1) * (mx[n][1] - mn[n][1] + 1);
		sx.clear(), sy.clear();
		for(int i = n; i >= 0; --i) {
			sx.insert(x), sy.insert(y);
			int Mx = *sx.rbegin(), Nx = *sx.begin();
			int My = *sy.rbegin(), Ny = *sy.begin();
			for(int t = 0; t < 4; ++t) {
				int NMx = max(Mx, mx[i][0] + dx[t]);
				int NNx = min(Nx, mn[i][0] + dx[t]);
				int NMy = max(My, mx[i][1] + dy[t]);
				int NNy = min(Ny, mn[i][1] + dy[t]);
				// printf("%d %d %d %d\n", NMx, NNx, NMy, NNy);
				maxn = min(maxn, 1ll * (NMx - NNx + 1) * (NMy - NNy + 1));
			}
			if(i) {
				int z = hz(lx[i]);
				x += dx[z], y += dy[z];
			}
		}
		// printf("%d %d\n", x, y);
		printf("%lld\n", maxn);
	}
	return 0;
}