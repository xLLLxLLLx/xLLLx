#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 4e5 + 10;
int n, k, tot = 0;
int tr[N], f[N];
ll a[N], all[N], qz[N];

int find(ll x) {
	return lower_bound(all + 1, all + 1 + tot, x) - all;
}

int lower(int x) {
	return x & (-x);
}

int get(int x) {
	int ans = 0;
	for(; x; x -= lower(x));
		ans = max(ans, tr[x]);
	return ans;
}

void upd(int x, int y) {
	printf("qwq%d %d\n", x, y);
	for(; x < N; x += lower(x))
		tr[x] = max(tr[x], y);
}

bool check(ll x) {
	tot = 0;
	for(int i = 1; i <= n; ++i) {
		all[++tot] = qz[i] - x;
		all[++tot] = qz[i];
	}
	for(int i = 1; i < N; ++i)
		tr[i] = 0;
	sort(all + 1, all + 1 + tot);
	tot = unique(all + 1, all + 1 + tot) - all - 1;
	for(int i = 1; i <= n; ++i) {
		f[i] = get(find(qz[i] - x)) + 1;
		if(f[i] >= k) return true;
		upd(find(a[i]), f[i]);
	}
	for(int i = 1; i <= n; ++i) {
		printf("%d %d\n", i, f[i]);
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		scanf("%d%d", &n, &k);
		for(int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);
			qz[i] = qz[i - 1] + a[i];
		}
		// ll l = -2e14, r = 1e9, ans = 0;
		// while(l <= r) {
		// 	ll mid = (l + r) >> 1;
		// 	if(check(mid)) {
		// 		r = mid - 1;
		// 		ans = mid;
		// 	} else {
		// 		l = mid + 1;
		// 	}
		// }
		// printf("%lld\n", ans);
		check(2);
	}
	return 0;
}