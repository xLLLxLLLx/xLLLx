#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int lift[N], elev[N];

int getl(int x, int tot, int *a) {
	int l = 1, r = tot, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(a[mid] >= x) ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	return ans;
}

int getr(int x, int tot, int *a) {
	int l = 1, r = tot, ans = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(a[mid] <= x) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	return ans;
}

int main() {
	int n, m, cl, ce, v;
	scanf("%d%d%d%d%d", &n, &m, &cl, &ce, &v);
	for(int i = 1; i <= cl; ++i) {
		scanf("%d", &lift[i]);
	}
	for(int i = 1; i <= ce; ++i) {
		scanf("%d", &elev[i]);
	}
	int q;
	scanf("%d", &q);
	for(int o = 1, x1, x2, y1, y2; o <= q; ++o) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		int ans = 1e9;
		int l = getl(y1, cl, lift), r = getr(y1, cl, lift);
		if(l) {
			int pos = abs(y1 - lift[l]) + abs(x1 - x2) + abs(y2 - lift[l]);
			ans = min(ans, pos);
		}
		if(r) {
			int pos = abs(y1 - lift[r]) + abs(x1 - x2) + abs(y2 - lift[r]);
			ans = min(ans, pos);
		}
		l = getl(y1, ce, elev), r = getr(y1, ce, elev);
		if(l) {
			int pos = abs(y1 - elev[l]) + abs(x1 - x2) / v + abs(y2 - elev[l]);
			if(abs(x1 - x2) % v) pos++;
			ans = min(ans, pos);
		}
		if(r) {
			int pos = abs(y1 - elev[r]) + abs(x1 - x2) / v + abs(y2 - elev[r]);
			if(abs(x1 - x2) % v) pos++;
			ans = min(ans, pos);
		}
		if(x1 == x2) ans = min(ans, abs(y1 - y2));
		// printf("%d %d %d %d\n", x1, x2, y1, y2);
		printf("%d\n", ans);
	}
	return 0;
}