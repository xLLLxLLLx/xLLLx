#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-6;
const int N = 55;
int ans = 1e9;
int w, h, n, m;
int a[N], b[N];

bool cmp(int x, int y) {
	return x > y;
}

double js(double d, double dis) {
	d /= 2.0, dis /= 2.0;
	return 2.0 * sqrt(d * d - dis * dis);
}

void go(int now, int flg) {
	double pos = 0.0;
	for(;;) {
		now++;
		// cout << pos << endl;
		if(now & 1) {
			int id = (now + 1) / 2;
			id -= flg;
			if(id > n || a[id] < w) break;
			pos += js(a[id], w);
			if((pos - h) >= -eps) {
				ans = min(ans, now - flg);
				break;
			}
		} else {
			int id = now / 2;
			if(id > m || b[id] < w) break;
			pos += js(b[id], w);
			if((pos - h) >= -eps) {
				ans = min(ans, now - flg);
				break;
			}
		}
	}
}

int main() {
	cin >> w >> h >> n >> m;
	// if(w > h) 
	swap(w, h);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &a[i]);
	for(int i = 1; i <= m; ++i)
		scanf("%d", &b[i]);
	sort(a + 1, a + 1 + n, cmp), sort(b + 1, b + 1 + m, cmp);
	go(0, 0), go(1, 1);
	if(ans == 1e9) puts("-1");
	else printf("%d\n", ans);
	return 0;
}