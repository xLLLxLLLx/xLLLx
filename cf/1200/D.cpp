#include <bits/stdc++.h>
using namespace std;
const int N = 2010;
int b[N][N], cb[N], ce[N], rb[N], re[N];

int main() {
	int n, k;
	scanf("%d%d", &n, &k);
	k = min(k, n);
	char ch;
	for(int i = 1; i <= n; ++i) {
		for(int j = 1; j <= n; ++j) {
			cin >> ch;
			if(ch == 'B') {
				if(!cb[j]) cb[j] = i;
				ce[j] = max(ce[j], i);
				if(!rb[i]) rb[i] = j;
				re[i] = max(re[i], j);
			}
		}
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		if(!ce[i]) ans++;
	for(int i = 1; i <= n; ++i)
		if(!re[i]) ans++;
	for(int i = 1; i <= n - k + 1; ++i) {
		int l = i, r = i + k - 1, now = 0, res = 0;
		for(int j = 1; j <= k; ++j) {
			if(cb[j] >= l && ce[j] <= r) now++;
			if(rb[j] >= l && re[j] <= r) res++;
		}
		b[i][1] += now;
		b[1][i] += res;
		for(int j = 2; j <= n - k + 1; ++j) {
			if(cb[j - 1] >= l && ce[j - 1] <= r) now--;
			if(rb[j - 1] >= l && re[j - 1] <= r) res--;
			if(cb[j + k - 1] >= l && ce[j + k - 1] <= r) now++;
			if(rb[j + k - 1] >= l && re[j + k - 1] <= r) res++;
			b[i][j] += now;
			b[j][i] += res;
		}
	}
	int maxn = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= n; ++j) {
			maxn = max(maxn, b[i][j]);
		}
	printf("%d\n", maxn + ans);
	return 0;
}