#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
struct data {
	int x, y;
} a[N];
int tr[N], all[N], vis[N], d[N];

bool cmp(data A, data B) {
	if(A.y != B.y) return A.y > B.y;
	else return A.x < B.x;
}

int lower(int x) {
	return x & (-x);
}

void upd(int x) {
	for(; x < N; x += lower(x)) tr[x]++;
}

int get(int x) {
	int ans = 0;
	for(; x; x -= lower(x)) ans += tr[x];
	return ans;
}

int main() {
	int n;
	scanf("%d", &n);
	int cnt = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].x, &a[i].y);
		all[++cnt] = a[i].x;
	}
	sort(all + 1, all + 1 + cnt);
	int m = unique(all + 1, all + 1 + cnt) - all - 1;
	for(int i = 1; i <= n; ++i) {
		a[i].x = lower_bound(all + 1, all + 1 + m, a[i].x) - all;
	}
	ll ans = 0, pos = 0;
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; ++i) {
		int now = i;
		d[0] = 0;
		for(; now <= n && a[now].y == a[i].y; now++) {
			d[++d[0]] = a[now].x;
			if(!vis[a[now].x]) {
				pos++, vis[a[now].x] = 1;
				upd(a[now].x);
			}
		}
		int last = 0;
		for(int i = 1; i <= d[0]; ++i) {
			int tmp = get(d[i]);
			ans += 1ll * (tmp - last) * (pos - tmp + 1);
			last = get(d[i]);
		}
		now--;
		i = now;
	}
	printf("%lld\n", ans);
	return 0;
}