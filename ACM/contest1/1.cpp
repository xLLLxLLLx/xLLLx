#include <bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1
#define ll long long
using namespace std;
const int N = 4e5 + 10;
struct data {
	int tp, x, y;
} q[N];
struct node {
	set<int> id;
} tr[N << 2];
int all[N * 3], tot, ans;

int get(int x) {
	return lower_bound(all + 1, all + 1 + tot, x) - all;
}

void upd(int x, int l, int r, int L, int R, int w) {
	if(L <= l && r <= R) {
		tr[x].id.insert(w);
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) upd(ls, l, mid, L, R, w);
	if(R > mid) upd(rs, mid + 1, r, L, R, w);
}

void ers(int x, int l, int r, int L, int R, int w) {
	if(L <= l && r <= R) {
		tr[x].id.erase(w);
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) ers(ls, l, mid, L, R, w);
	if(R > mid) ers(rs, mid + 1, r, L, R, w);
}

ll pf(ll x) {
	return x * x;
}

bool check(int i, int j) {
	return pf(q[i].x - q[j].x) + pf(q[i].y - q[j].y) < pf(q[i].y);
}

void get(int x, int l, int r, int L, int w) {
	set<int> :: iterator sit;
	for(sit = tr[x].id.begin(); sit != tr[x].id.end(); ++sit) {
		int pos = *sit;
		if(check(pos, w)) {
			// printf("q%d %d\n", q[pos].x, q[pos].y);
			// printf("p%d %d\n", q[w].x, q[w].y);
			ans = pos;
		}
	}
	int mid = (l + r) >> 1;
	if(l == r || ans != -1) return ;
	if(L <= mid) get(ls, l, mid, L, w);
	else get(rs, mid + 1, r, L, w);
}

int main() {
	int n, cnt = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d%d", &q[i].tp, &q[i].x, &q[i].y);
		if(q[i].tp == 1) {
			all[++cnt] = q[i].x - q[i].y, all[++cnt] = q[i].x + q[i].y; 
		} else {
			all[++cnt] = q[i].x;
		}
	}
	sort(all + 1, all + 1 + cnt);
	tot = unique(all + 1, all + 1 + cnt) - all - 1;
	for(int i = 1; i <= n; ++i) {
		if(q[i].tp == 1) {
			int l = get(q[i].x - q[i].y);
			int r = get(q[i].x + q[i].y);
			upd(1, 1, tot, l, r, i);
		} else {
			int x = get(q[i].x);
			ans = -1;
			get(1, 1, tot, x, i);
			printf("%d\n", ans);
			if(ans != -1) {
				int l = get(q[ans].x - q[ans].y);
				int r = get(q[ans].x + q[ans].y);
				ers(1, 1, tot, l, r, ans);
			}
		}
	}
	return 0;
}