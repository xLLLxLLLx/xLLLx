#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 6e6 + 10;
ll ans = 0, ans1 = 0, ans2 = 0;
int res = 0, now = 0, n, root;
int ls[N], rt[N], ch[N][2], rs[N], a[N], sum[N];

void read(int &x) {
	x = ++ res;
	scanf("%d", &a[x]);
	if(a[x]) {
		return ;
	}
	read(ch[x][0]), read(ch[x][1]);
}

void build(int &x, int l, int r, int L) {
	x = ++now;
	if(l == r) {
		sum[x] = 1;
		return ;
	}
	int mid = (l + r) >> 1;
	if(L <= mid) {
		build(ls[x], l, mid, L);
	} else {
		build(rs[x], mid + 1, r, L);
	}
	sum[x] = sum[ls[x]] + sum[rs[x]];
}

int merge(int x, int y) {
	if(!x) return y;
	if(!y) return x;
	ans1 += 1ll * sum[rs[x]] * sum[ls[y]];
	ans2 += 1ll * sum[ls[x]] * sum[rs[y]];
	ls[x] = merge(ls[x], ls[y]);
	rs[x] = merge(rs[x], rs[y]);
	sum[x] = sum[ls[x]] + sum[rs[x]];
	return x;
}

void work(int x) {
	if(!x) {
		return ;
	}
	work(ch[x][0]), work(ch[x][1]);
	if(a[x]) return ;
	ans1 = 0, ans2 = 0;
	rt[x] = merge(rt[ch[x][0]], rt[ch[x][1]]);
	ans += min(ans1, ans2);
}

int main() {
	int n;
	scanf("%d", &n);
	read(root);
	for(int i = 1; i <= res; ++i) {
		if(a[i]) {
			build(rt[i], 1, n, a[i]);
		}
	}
	work(1);
	printf("%lld\n", ans);
	return 0;
}
