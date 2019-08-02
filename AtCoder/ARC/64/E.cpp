#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
const double inf = 1e-12;
struct Point {
	double x, y;
} c[N];
int vis[N];
double R[N], f[N];

double pf(double x) {
	return x * x;
}

double dis(Point A, Point B) {
	return sqrt(pf(A.x - B.x) + pf(A.y - B.y));
}

double get(int k, int j) {
	return max(0.0, dis(c[k], c[j]) - (R[k] + R[j]));
}

int main() {
	for(int i = 1; i <= 2; ++i) {
		scanf("%lf%lf", &c[i].x, &c[i].y);
		R[i] = 0;
	}
	int n;
	scanf("%d", &n);
	n += 2;
	for(int i = 1; i <= n; ++i) f[i] = 3e9;
	for(int i = 3; i <= n; ++i) {
		scanf("%lf%lf%lf", &c[i].x, &c[i].y, &R[i]);
	}
	f[1] = 0;
	for(;;) {
		int be = -1;
		for(int i = 1; i <= n; ++i) {
			if(vis[i]) continue;
			if(be == -1 || f[be] > f[i]) be = i;
		}
		if(be == -1) break;
		vis[be] = 1;
		for(int i = 1; i <= n; ++i) {
			f[i] = min(f[i], f[be] + get(i, be));
		}
	}
	printf("%.12f\n", f[2]);
	return 0;
}