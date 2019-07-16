#include<bits/stdc++.h>
#define ls x << 1
#define rs x << 1 | 1
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data {
	int l, r;
} xd[N];
struct node {
	int js, os;
} tr[N << 2];
vector<int> b[N], e[N];
int a[N], all[N << 2];
int rev[N << 2], n, k;

int getl(int x) {
	int l = 1, r = n, ans = 1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(all[mid] >= x) r = mid - 1, ans = mid;
		else l = mid + 1;
	}
	return ans;
}

int getr(int x) {
	int l = 1, r = n, ans = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(all[mid] <= x) l = mid + 1, ans = mid;
		else r = mid - 1;
	}
	return ans;
}

node merge(node A, node B) {
	node res;
	res.js = A.js + B.js;
	res.os = A.os + B.os;
	return res;
}

void build(int x, int l, int r) {
	if(l == r) {
		tr[x].os = 1;
		tr[x].js = 0;
		return ;
	}
	int mid = (l + r) >> 1;
	build(ls, l, mid), build(rs, mid + 1, r);
	tr[x] = merge(tr[ls], tr[rs]);
}

void down(int x) {
	if(rev[x]) {
		rev[x] = 0;
		rev[ls] ^= 1;
		rev[rs] ^= 1;
		swap(tr[ls].os, tr[ls].js);
		swap(tr[rs].os, tr[rs].js);
	}
}

void put(int x, int l, int r, int L, int R) {
	// printf("x=%d l=%d r=%d\n", x,l,r);
	if(L <= l && r <= R) {
		rev[x] ^= 1;
		swap(tr[x].os, tr[x].js);
		// printf("qwqx=%d l=%d r=%d os=%d js=%d\n",x,l,r,tr[x].js,tr[x].os);
		return ;
	}
	down(x);
	int mid = (l + r) >> 1;
	if(L <= mid) put(ls, l, mid, L, R);
	if(R > mid) put(rs, mid + 1, r, L, R);
	tr[x] = merge(tr[ls], tr[rs]);
	// printf("x=%d l=%d r=%d os=%d js=%d\n", x, l, r, tr[x].os,tr[x].js);
}

node get(int x, int l, int r, int L, int R) {
	if(L > R) {
		return (node){0, 0};
	}
	if(L <= l && r <= R) {
		return tr[x];
	}
	down(x);
	int mid = (l + r) >> 1;
	node ans1, ans2;
	if(L <= mid) ans1 = get(ls, l, mid, L, R);
	else ans1.js = ans1.os = 0;
	if(R > mid) ans2 = get(rs, mid + 1, r, L, R);
	else ans2.js = ans2.os = 0;
	tr[x] = merge(tr[ls], tr[rs]);
	return merge(ans1, ans2);
}

int main() {
	scanf("%d%d", &n, &k);
	int res = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a[i]);
		all[i] = a[i];
	}
	sort(a + 1, a + 1 + n), sort(all + 1, all + 1 + n);
	for(int i = 1; i <= n; ++i) {
		a[i] = lower_bound(all + 1, all + 1 + n, a[i]) - all;
	}
	for(int i = 1; i <= k; ++i) {
		scanf("%d%d", &xd[i].l, &xd[i].r);
		xd[i].l = getl(xd[i].l);
		xd[i].r = getr(xd[i].r);
		b[xd[i].l].push_back(i), e[xd[i].r].push_back(i);
	}
	ll ans = 1ll * n * (n - 1) * (n - 2) / 6;
	build(1, 1, n);
	for(int i = 1, len; i <= n; ++i) {
		// printf("qwq%d\n", i);
		len = b[i].size();
		for(int j = 0; j < len; ++j) {
			// printf("%d %d\n", xd[b[i][j]].l, xd[b[i][j]].r);
			put(1, 1, n, xd[b[i][j]].l, xd[b[i][j]].r);
		}
		ll tmp = 0;
		tmp += get(1, 1, n, 1, i - 1).os + get(1, 1, n, i + 1, n).js;
		// printf("%lld\n", tmp);
		ans -= tmp * (tmp - 1) / 2;
		len = e[i].size();
		for(int j = 0; j < len; ++j) {
			put(1, 1, n, xd[e[i][j]].l, xd[e[i][j]].r);
		}
	}
	printf("%lld\n", ans);
	return 0;
}