#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
vector<int> g[N];
int a[N][26], v[N];
double c[N];
char lx[N];
//renshazidaidachangshu
int main() {
	scanf("%s", lx + 1);
	int n = strlen(lx + 1);
	for(int i = 1; i <= n; ++i) {
		v[i] = lx[i] - 'a' + 1;
		g[v[i]].push_back(i);
	}
	double ans = 0;
	for(int i = 1; i <= 26; ++i) {
		int len = g[i].size();
		if(!len) continue;
		for(int j = 0; j < len; ++j) {
			int fi = g[i][j];
			for(int k = fi; k <= n; ++k) {
				a[k - fi + 1][v[k]]++;
				// printf("%c", char(v[k] + 'a' - 1));
			}
			for(int k = 1; k < fi; ++k) {
				a[n - fi + 1 + k][v[k]]++;
				// printf("%c", char(v[k] + 'a' - 1));
			}
			// puts("");
		}
		int tmp = 0;
		for(int j = 1; j <= n; ++j) {
			int pos = 0;
			for(int k = 1; k <= 26; ++k) {
				pos += (a[j][k] == 1);
				a[j][k] = 0;
			}
			tmp = max(tmp, pos);
		}
		ans += (double)tmp / (double) n;
	}
	printf("%.12f\n", ans);
	return 0;
}