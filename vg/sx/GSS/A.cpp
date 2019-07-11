#include <bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int N = 5e4 + 10, inf = -1e9;
struct data {
	int sum, mx, lmx, rmx;
	data() {
		mx = lmx = rmx = inf;
		sum = 0;
	}
} tr[N << 2];

data merge(data A, data B) {
	data res;
	res.sum = A.sum + B.sum;
	res.lmx = max(A.lmx, A.sum + B.lmx);
	res.rmx = max(B.rmx, B.sum + A.rmx);
	res.mx = max(res.lmx, res.rmx);
	res.mx = max(res.mx, A.rmx + B.lmx);
	return res;
}

void build(int x, int l, int r) {
	if(l == r) {
		int val;
		scanf("%d", &val);
		tr[x].sum = tr[x].mx = tr[x].lmx = tr[x].rmx = val;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	tr[x] = merge(tr[ls], tr[rs]);
}

data get(int x, int l, int r, int L, int R) {
	if(L <= l && r <= R) {
		return tr[x];
	}
	int mid = (l + r) >> 1;
	if(R <= mid) {
		return get(ls, l, mid, L, R);
	} else if(L > mid) {
		return get(rs, mid + 1, r, L, R);
	} else {
		return merge(get(ls, l, mid, L, R), get(rs, mid + 1, r, L, R));
	}
}

int main() {
	int n;
	scanf("%d", &n);
	build(1, 1, n);
	int T;
	scanf("%d", &T);
	for(int o = 1, l, r; o <= T; ++o) {
		scanf("%d%d", &l, &r);
		printf("%d\n", get(1, 1, n, l, r).mx);
	}
	return 0;
}