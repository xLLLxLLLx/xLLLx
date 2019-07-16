#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3010;
ll qz[N][N];
int a[N][N], len[N], now[N], all[N], num[N];

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &x, &y);
		all[i] = y;
		a[x][++len[x]] = y;
	}
	sort(all + 1, all + 1 + n);
	int tot = unique(all + 1, all + 1 + n) - all - 1;
	for(int i = 2; i <= m; ++i) {
		if(!len[i]) continue;
		sort(a[i] + 1, a[i] + 1 + len[i]);
		for(int j = 1; j <= len[i]; ++j) {
			qz[i][j] = qz[i][j - 1] + a[i][j];
			a[i][j] = lower_bound(all + 1, all + 1 + tot, a[i][j]) - all;
			num[a[i][j]]++;
		}
	}
	ll ans = 1e18;
	for(int i = 1; i <= m; ++i) now[i] = 1;
	for(int i = n; i >= 0; --i) {
		ll pos = 0;
		int sum = 0, maxn = 0;
		for(int j = 2; j <= m; ++j) {
			if(len[j] <= i) {
				sum += len[j];
				maxn = max(maxn, len[j]);
				continue;
			} else {
				maxn = max(maxn, i);
				sum += i;
				pos += qz[j][len[j] - i];
				num[a[j][now[j]]]--;
				now[j]++;
			}
		}
		if(n - sum <= maxn) {
			int tmp = maxn - (n - sum) + 1;
			// printf("pos=%lld maxn=%d sum=%d\n", pos,maxn,sum);
			for(int j = 1; j <= tot; ++j) {
				if(num[j] <= tmp) {
					tmp -= num[j];
					pos += 1ll * num[j] * all[j];
				} else {
					pos += 1ll * tmp * all[j];
					tmp = 0;
				}
				if(!tmp) break;
			}
			if(tmp) continue;
		}
		ans = min(ans, pos);
	}
	printf("%lld\n", ans);
	return 0;
}