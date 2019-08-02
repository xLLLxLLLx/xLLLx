#include <bits/stdc++.h>
using namespace std;
const int N = 3e5 + 10, LOG = 20;
const double Cir = acos(-1.0) * 2.0, eps = 1e-10;
struct data {
	double l, r;
} a[N];
double dis[N], kk[N];
int n, k, f[N][LOG + 1];

bool cmp(data A, data B) {
	return A.r < B.r;
}

bool check(double len) {
	for(int i = 1; i <= n; ++i) {
		double gg = acos(len / dis[i]);
		a[i].l = kk[i] - gg, a[i].r = kk[i] + gg;
		while(a[i].r < 0) a[i].l += Cir, a[i].r += Cir;
		while(a[i].r >= Cir) a[i].l -= Cir, a[i].r -= Cir;
		// cout<<a[i].l << " "<< a[i].r <<" "<<gg<<endl;
	}
	int tot = n;
	sort(a + 1, a + 1 + tot, cmp);
	for(int i = 1; i <= tot; ++i) a[i + tot] = (data){a[i].l + Cir, a[i].r + Cir};
	tot <<= 1;
	int last = 0;
	for(int i = 1; i <= tot; ++i) {
		last = max(last, i);
		for(; last <= tot && a[last].l <= a[i].r; last++);
		f[i][0] = last;
	}
	for(int j = 1; j <= LOG; ++j)
		for(int i = 1; i <= tot; ++i)
			f[i][j] = f[f[i][j - 1]][j - 1];
	// for(int i = 1; i <= tot; ++i)
	// 	for(int j = 0; j <= LOG; ++j) {
	// 		if(f[i][j]) {
	// 			printf("f[%d][%d]=%d\n", i, j, f[i][j]);
	// 		}
	// 	}
	for(int be = 1; be <= n; ++be) {
		int pos = 0, now = be;
		for(int t = k; t; t >>= 1, pos++) {
			if(t & 1) now = f[now][pos];
		}
		if(!now || now > be + n - 1) return true;
	}
	return false;
}

int main() {
	scanf("%d%d", &n, &k);
	double l = 0, r = 3e5;
	for(int i = 1; i <= n; ++i) {
		double x, y;
		scanf("%lf%lf", &x, &y);
		dis[i] = sqrt(x * x + y * y), kk[i] = atan2(y, x);
		r = min(r, dis[i]);
	}
	while(r - l > eps) {
		double mid = (l + r) / 2.0;
		if(check(mid)) l = mid;
		else r = mid;
	}
	printf("%.10f\n", l);
	return 0;
}