#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
char lx[N];
int v[N], tr[4][11][11][N];

int lower(int x) {
	return x & (-x);
}

void add(int *a, int x, int k) {
	for(int i = x; i < N; i += lower(i)) {
		a[i] += k;
	}
}

int get(int *a, int x) {
	int ans = 0;
	for(int i = x; i; i -= lower(i)) {
		ans += a[i];
	}
	return ans;
}

int zh(char ch) {
	if(ch == 'A') return 0;
	if(ch == 'T') return 1;
	if(ch == 'G') return 2;
	if(ch == 'C') return 3;
}

int main() {
	scanf("%s", lx + 1);
	int n = strlen(lx + 1);
	for(int i = 1; i <= 10; ++i) {
		for(int j = 1; j <= n; ++j) {
			v[j] = zh(lx[j]);
			add(tr[v[j]][i][j % i], j, 1);
		}
	}
	int m;
	scanf("%d", &m);
	for(int o = 1, tp; o <= m; ++o) {
		scanf("%d", &tp);
		if(tp == 2) {
			int l, r, ans = 0;
			scanf("%d%d%s", &l, &r, lx + 1);
			int len = strlen(lx + 1);
			for(int i = 1; i <= min(r - l + 1, len); ++i) {
				int gg = zh(lx[i]), tmp = (l + i - 1) % len;
				int pos = get(tr[gg][len][tmp], r) - get(tr[gg][len][tmp], l - 1);
				ans += pos;
			}
			printf("%d\n", ans);
		} else {
			int x;
			scanf("%d%s", &x, lx + 1);
			int y = zh(lx[1]);
			for(int i = 1; i <= 10; ++i) {
				add(tr[v[x]][i][x % i], x, -1);
				add(tr[y][i][x % i], x, 1);
			}
			v[x] = y;
		}
	}
	return 0;
}