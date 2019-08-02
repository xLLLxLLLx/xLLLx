#include <bits/stdc++.h>
using namespace std;
const int N = 3e6 + 10;
struct data {
	int l, r, id;
} a[N];
int d[N];
string lx[N];

bool cmp(data A, data B) {
	return A.l == B.l ? A.r > B.r : A.l < B.l;
}

int main() {
	int n, maxn = 0;
	scanf("%d", &n);
	int cnt = 0;
	for(int o = 1, num; o <= n; ++o) {
		cin >> lx[o];
		scanf("%d", &num);
		int len = lx[o].size();
		for(int t = 1, be; t <= num; ++t) {
			scanf("%d", &be);
			maxn = max(maxn, be + len - 1);
			a[++cnt].l = be, a[cnt].r = be + len - 1, a[cnt].id = o;
		}
	}
	sort(a + 1, a + 1 + cnt, cmp);
	int last = 0;
	for(int i = 1; i <= cnt; ++i) {
		for(int j = max(last, a[i].l); j <= a[i].r; ++j) {
			d[j] = lx[a[i].id][j - a[i].l] - 'a' + 1;
		}
		last = max(last, a[i].r + 1);
	}
	for(int i = 1; i <= maxn; ++i) {
		if(!d[i]) d[i] = 1;
		printf("%c", char(d[i] + 'a' - 1));
	}
	puts("");
	return 0;
}