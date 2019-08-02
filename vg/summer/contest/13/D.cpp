#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct data {
	int w, t, id;
} a[N], b[N];
int ans = 0, n, T;
int d[N], c[N];

bool cmp(data A, data B) {
	return A.w < B.w;
}

bool comp(data A, data B) {
	return A.t < B.t;
}

int getl(int x) {
	int l = 1, r = n, gg = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(a[mid].w >= x) gg = mid, r = mid - 1;
		else l = mid + 1;
	}
	return gg;
}

int get(int x) {
	int l = getl(x);
	if(l == -1) {
		return 0;
	}
	int tot = 0, pos = 0, now = T;
	for(int i = l; i <= n; ++i) b[++tot] = a[i];
	c[0] = 0;
	sort(b + 1, b + 1 + tot, comp);
	for(int i = 1; i <= tot; ++i) {
		if(now >= b[i].t) {
			c[++c[0]] = b[i].id;
			pos++;
		}
		now -= b[i].t;
		if(now <= 0) break;
	}
	c[0] = min(c[0], x);
	pos = min(pos, x);
	if(pos > ans) {
		ans = pos;
		for(int i = 0; i <= c[0]; ++i) {
			d[i] = c[i];
		}
	}
	return pos;
}

int main() {
	scanf("%d%d", &n, &T);
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &a[i].w, &a[i].t);
		a[i].id = i;
	}
	sort(a + 1, a + 1 + n, cmp);
	int l = 0, r = n;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(get(mid) == mid) l = mid + 1;
		else r = mid - 1;
	}
	printf("%d\n", ans);
	printf("%d\n", d[0]);
	for(int i = 1; i <= d[0]; ++i) {
		printf("%d ", d[i]);
	}
	return 0;
}