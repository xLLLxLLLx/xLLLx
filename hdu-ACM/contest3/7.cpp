#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
#define ls (x << 1)
#define rs (x << 1 | 1)
int num[N << 2];
ll sum[N << 2], all[N], a[N];

void change(int x, int l, int r, int L) {
	if(l == r) {
		num[x]++;
		sum[x] += all[l];
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) change(ls, l, mid, L);
	else change(rs, mid + 1, r, L);
	sum[x] = sum[ls] + sum[rs];
	num[x] = num[ls] + num[rs];
}

int get(int x, int l, int r, ll w) {
	if(w <= 0) return 0;
	if(l == r) {
		int tmp = w / all[l];
		if(w % all[l]) tmp++;
		return tmp;
	}
	int mid = (l + r) >> 1;
	if(sum[rs] < w) {
		return num[rs] + get(ls, l, mid, w - sum[rs]);
	} else if(sum[rs] == w) {
		return num[rs];
	} else {
		return get(rs, mid + 1, r, w);
	}
}

int main() {
	int T;
	scanf("%d", &T);
	for(int o = 1; o <= T; ++o) {
		int n; ll m;
		scanf("%d%lld", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%lld", &a[i]);
			all[i] = a[i];
		}
		sort(all + 1, all + 1 + n);
		int tot = unique(all + 1, all + 1 + n) - all - 1;
		for(int i = 1; i <= tot * 4; ++i)
			sum[i] = num[i] = 0;
		ll qz = 0;
		for(int i = 1; i <= n; ++i) {
			qz += a[i];
			printf("%d ", get(1, 1, tot, qz - m));
			int pos = lower_bound(all + 1, all + 1 + tot, a[i]) - all;
			change(1, 1, tot, pos);
		}
		puts("");
	}
	return 0;
}