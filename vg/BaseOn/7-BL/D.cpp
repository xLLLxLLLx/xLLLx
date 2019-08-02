#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 20;
struct data {
	int l, r;
} a[N], b[N];
int all[N * 10], f[N * 4][LOG + 1];

int get(int x, int tot) {
	return lower_bound(all + 1, all + 1 + tot, x) - all;
}

int main() {
	int n, m;
	while(scanf("%d%d", &n, &m) == 2) {
		int cnt = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d%d", &a[i].l, &a[i].r);
			all[++cnt] = a[i].l, all[++cnt] = a[i].r;
		}
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d", &b[i].l, &b[i].r);
			all[++cnt] = b[i].l, all[++cnt] = b[i].r;
		}
		sort(all + 1, all + 1 + cnt);
		int tot = unique(all + 1, all + 1 + cnt) - all - 1;
		for(int j = 0; j <= LOG; ++j)
			for(int i = 1; i <= tot; ++i) {
				f[i][j] = 1e9;
		}
		for(int i = 1; i <= n; ++i) {
			a[i].l = get(a[i].l, tot), a[i].r = get(a[i].r, tot);
			f[a[i].l][0] = min(f[a[i].l][0], a[i].r);
		}
		for(int i = tot - 1; i >= 1; --i) {
			f[i][0] = min(f[i + 1][0], f[i][0]);
		}
		for(int j = 1; j <= LOG; ++j) 
			for(int i = 1; i <= tot; ++i) {
				if(f[i][j - 1] != 1e9) f[i][j] = f[f[i][j - 1]][j - 1];
			}
		// puts("XXX");
		for(int i = 1; i <= m; ++i) {
			b[i].l = get(b[i].l, tot), b[i].r = get(b[i].r, tot);
			int pos = 0, now = b[i].l;
			for(int j = LOG; j >= 0; --j) {
				if(f[now][j] > b[i].r) continue;
				now = f[now][j];
				pos += (1 << j);
			}
			printf("%d\n", pos);
		}
	}
	return 0;
}