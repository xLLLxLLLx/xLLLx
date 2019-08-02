#include <bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1
using namespace std;
const int N = 1e6 + 1, LOG = 29;
int n, m, val;
struct data {
	data() {
		len = 0;
	}
	void clr() {
		len = 0;
		memset(a, 0, sizeof a);
	}
	int len, a[LOG + 1];
} tr[N << 2], gg;

void read(int &x) {
	char ch = getchar(); x = 0;
	for(;ch < '0' || ch > '9'; ch = getchar()) ;
	for(;ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

data merge(data A, data B) {
	if(A.len == 30) return A;
	if(B.len == 30) return B;
	for(int i = LOG; i >= 0; --i) {
		if(!A.a[i]) continue;
		for(int j = i; j >= 0; --j) {
			if((A.a[i] >> j) & 1) {
				if(!B.a[j]) {
					B.a[j] = A.a[i];
					B.len++;
					break;
				} else A.a[i] ^= B.a[j];
			}
		}
	}
	return B;
}

inline void build(int x, int l, int r) {
	if(l == r) {
		if(l <= n) read(val);
		else val = 0;
		for(int i = LOG; i >= 0; --i) {
			if((val >> i) & 1) {
				tr[x].a[i] = val;
				tr[x].len++;
				break;
			}
		}
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	tr[x] = merge(tr[ls], tr[rs]);
}

inline void get(int x, int l, int r, int L, int R) {
	if(gg.len == 30) return ;
	if(L <= l && r <= R) {
		gg = merge(gg, tr[x]);
		return ;
	}
	int mid = (l + r) >> 1;
	if(R <= mid) get(ls, l, mid, L, R);
	else if(L > mid) get(rs, mid + 1, r, L, R);
	else {
		get(ls, l, mid, L, R), get(rs, mid + 1, r, L, R);
	}
}

inline void change(int x, int l, int r, int L, int w) {
	if(l == r) {
		for(int i = LOG; i >= 0; --i) {
			if((w >> i) & 1) {
				tr[x].a[i] = w;
				tr[x].len++;
				break;
			}
		}
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) change(ls, l, mid, L, w);
	else change(rs, mid + 1, r, L, w);
	tr[x] = merge(tr[ls], tr[rs]);
}

int cal(data A) {
	int ans = 0;
	for(int i = LOG; i >= 0; --i) {
		if(!((ans >> i) & 1)) {
			ans ^= A.a[i];
		}
	}
	return ans;
}

int main() {
	int T;
	read(T);
	for(int o = 1; o <= T; ++o) {
		read(n), read(m);
		int tot = n + m;
		build(1, 1, tot);
		int last = 0;
		for(int i = 1, tp; i <= m; ++i) {
			scanf("%d", &tp);
			if(tp == 0) {
				int l, r;
				read(l), read(r);
				l ^= last, r ^= last;
				l = (l % n) + 1, r = (r % n) + 1;
				if(l > r) swap(l, r);
				gg.clr();
				get(1, 1, tot, l, r);
				last = cal(gg);
				printf("%d\n", last);
			} else {
				int x;
				read(x);
				x ^= last;
				n++;
				change(1, 1, tot, n, x);
			}
		}
		for(int i = 1; i <= tot * 4; ++i) 
			tr[i].clr();
	}
	return 0;
}