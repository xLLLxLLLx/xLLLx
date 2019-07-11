#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 25;
int a[LOG][N], d[LOG], c[LOG], ans = 100, now = 0;

void work(int t, int n) {
	if(t >= 20) {
		int flg = 1;
		for(int i = 1; i <= n; ++i) {
			if(a[t][i]) flg = 0;
		}
		if(flg && now < ans) {
			ans = now;
			for(int i = 1; i <= now; ++i) {
				d[i] = c[i];
			}
		}
		return ;
	}
	int flg = 1;
	for(int i = 1; i <= n; ++i)
		if(a[t][i] & 1) {
			flg = 0;
			break;
		}
	if(flg) {
		for(int i = 1; i <= n; ++i) {
			a[t + 1][i] = a[t][i] / 2;
		}
		sort(a[t + 1] + 1, a[t + 1] + 1 + n);
		int m = unique(a[t + 1] + 1, a[t + 1] + 1 + n) - a[t + 1] - 1;
		work(t + 1, m);
	} else {
		for(int i = -1; i <= 1; i += 2){
			for(int j = 1; j <= n; ++j) 
				if(a[t][j] & 1)
					a[t + 1][j] = (a[t][j] + i) / 2;
				else a[t + 1][j] = a[t][j] / 2;
			sort(a[t + 1] + 1, a[t + 1] + 1 + n);
			int m = unique(a[t + 1] + 1, a[t + 1] + 1 + n) - a[t + 1] - 1;
			c[++now] = -i * (1 << t);
			work(t + 1, m);
			--now;
		}
	}
}

int main() {
	int n;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[0][i]);
	}
	sort(a[0] + 1, a[0] + 1 + n);
	int m = unique(a[0] + 1, a[0] + 1 + n) - a[0] - 1;
	work(0, m);
	printf("%d\n", ans);
	for(int i = 1; i <= ans; ++i) {
		printf("%d ", d[i]);
	}
	return 0;
}
