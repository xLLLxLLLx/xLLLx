#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
struct data {
	int l, r;
} a[N];
int mx[N], bsz, nl = 1, nr = 0, jx = 0, px = 0, n;

bool cmp(data A, data B) {
	return (A.l / bsz == B.l / bsz) ? A.r < B.r : A.l / bsz < B.l / bsz;
}

void add(int x) {
	if(nl <= mx[x] && mx[x] <= nr) px++, jx--;
	else jx++;
}

void del(int x) {
	if(nl <= mx[x] && mx[x] <= nr) px--, jx++;
	else jx--;
}

int main() {
	scanf("%d", &n);
	bsz = sqrt(n * 2.0);
	for(int i = 1, x, y; i <= n; ++i) {
		scanf("%d%d", &a[i].l, &a[i].r);
		mx[a[i].l] = a[i].r, mx[a[i].r] = a[i].l;
		if(a[i].l > a[i].r) swap(a[i].l, a[i].r);
	}
	sort(a + 1, a + 1 + n, cmp);
	ll ans = 1ll * n * (n - 1) * (n - 2) / 6, pos = 0, tmp = 0;
	for(int i = 1; i <= n; ++i) {
		// printf("qwq%d %d\n", a[i].l, a[i].r);
		while(nl > a[i].l) add(--nl);
		while(nr < a[i].r) add(++nr);
		while(nl < a[i].l) del(nl++);
		while(nr > a[i].r) del(nr--);
		// printf("%lld %lld\n", jx, px);
		pos += 1ll * jx * (n - 1 - jx);
		tmp += 1ll * (px - 1) * (n - px - jx);
	}
	ans -= pos / 2 + tmp;
	printf("%lld\n", ans);
	return 0;
}