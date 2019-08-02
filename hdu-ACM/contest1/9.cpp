#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 30;
int k;
char lx[N];
vector<int> g[M];
int vis[M], hz[N][M], b[N], a[N], L[M], R[M], nm[M];

bool check(int x, int z, int y) {
	// printf("x%d %d %d\n", x, z, y);
	int ans = 0;
	for(int i = 1; i <= 26; ++i) {
		if(i == z) continue;
		ans += L[i];
		if(min(hz[x][i], y) < L[i]) return false;
	}
	// printf("ans=%d\n", ans);
	if(ans > y) return false;
	return true;
}

int main() {
	// printf("!!!\n");
	while(~scanf("%s%d", lx + 1, &k)) {
		for(int i = 1; i <= 26; ++i) {
			nm[i] = vis[i] = 0;
			g[i].clear();
			scanf("%d%d", &L[i], &R[i]);
		}
		// printf("????\n");
		int len = strlen(lx + 1);
		for(int i = 1; i <= len; ++i) {
			a[i] = lx[i] - 'a' + 1;
			g[a[i]].push_back(i);
			nm[a[i]]++;
		}
		for(int j = 1; j <= 26; ++j) hz[len + 1][j] = 0;
		for(int i = len; i >= 1; --i) {
			for(int j = 1; j <= 26; ++j) hz[i][j] = hz[i + 1][j];
			hz[i][a[i]]++;
		}
		int flg = 0, tot = 0, gg = 0;
		for(int i = 1; i <= 26; ++i) {
			tot += L[i];
			gg += min(R[i], nm[i]);
			if(nm[i] < L[i]) {
				flg = 1;
				break;
			}
		}
		if(flg || tot > k || gg < k) {
			puts("-1");
			continue;
		}
		int now = 0;
		for(int i = 1; i <= k; ++i) {
			for(int j = 1; j <= 26; ++j) {
				if(R[j] >= 1) {
					int be = -1;
					for(int k = vis[j]; k < nm[j]; ++k) {
						if(g[j][k] > now) {
							be = k;
							break;
						}
					}
					if(be == -1) continue;
					// printf("%d %d %d\n", i, j, g[j][be]);
					vis[j] = be;
					if(check(g[j][be], j, k - i - max(L[j] - 1, 0))) {
						b[i] = j;
						now = g[j][be];
						L[j]--, R[j]--;
						L[j] = max(L[j], 0);
						break;
					}
				}
			}
			// printf("%d %d\n", i, b[i]);
		}
		// printf("XXXX\n");
		for(int i = 1; i <= k; ++i) {
			printf("%c", char(b[i] + 'a' - 1));
		}
		puts("");
	}
	return 0;
}