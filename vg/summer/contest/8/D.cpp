#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2010;
struct data {
	ll x, y;
	data() { x = y = 0; }
	data(ll _x, ll _y) { x = _x, y = _y; }
	data operator - (data C) { return data(x - C.x, y - C.y); }
} a[N];
struct line {
	int x, y;
	data p;
} b[N * N];
int rk[N], id[N];

bool cmp(data A, data B) {
	return A.x == B.x ? A.y < B.y : A.x < B.x;
}

ll cross(data A, data B) {
	return A.x * B.y - A.y * B.x;
}

bool comp(line A, line B) {
	return cross(A.p, B.p) > 0;
}

ll Abs(ll x) {
	if(x < 0) x = -x;
	return x;
}

ll S;

int main() {
	int n;
	scanf("%d%lld", &n, &S);
	S *= 2ll;
	for(int i = 1; i <= n; ++i) {
		scanf("%lld%lld", &a[i].x, &a[i].y);
	}
	sort(a + 1, a + 1 + n, cmp);
	for(int i = 1; i <= n; ++i) {
		id[i] = rk[i] = i;
	}
	int m = 0;
	for(int i = 1; i <= n; ++i) 
		for(int j = i + 1; j <= n; ++j) {
			b[++m].x = i, b[m].y = j;
			b[m].p = a[j] - a[i];
		}
	sort(b + 1, b + 1 + m, comp);
	for(int i = 1; i <= m; ++i) {
		int zd = b[i].x, yd = b[i].y;
		if(rk[zd] > rk[yd]) swap(zd, yd);
		int l = 1, r = rk[zd] - 1;
		while(l <= r) {
			int mid = (l + r) >> 1;
			ll Area = Abs(cross(b[i].p, a[id[mid]] - a[zd]));
			if(Area == S) {
				printf("Yes\n");
				printf("%lld %lld\n", a[zd].x, a[zd].y);
				printf("%lld %lld\n", a[yd].x, a[yd].y);
				printf("%lld %lld\n", a[id[mid]].x, a[id[mid]].y);
				return 0;
			} else if(Area > S) l = mid + 1;
			else r = mid - 1;
		}
		swap(rk[zd], rk[yd]);
		swap(id[rk[zd]], id[rk[yd]]);
	}
	puts("No");
	return 0;
}