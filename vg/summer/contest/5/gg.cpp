#include<cstdio>
#include<algorithm>
#include<map>
#define pll pair<long long ,long long>
using namespace std;
int n, m;
map<pll, int>Map;
bool B[3][5210];
struct point {
	long long x, y, z;
	point() {}
	point(long long x_, long long y_, long long z_ = 1) {
		x = x_, y = y_, z = z_;
	}
	point operator -(const point &p)const {
		return { x - p.x,y - p.y };
	}
	bool operator < (const point &p)const {
		return y*p.x < p.y*x;
	}
	long long SZ() {
		return x*x + y*y;
	}
}w[5210], P[5210];
struct Order {
	pll a;
	int num;
	bool operator<(const Order &p)const {
		return num < p.num;
	}
}U[2010000];
point To1(point a) {
	if (a.x < 0 || (a.x == 0 && a.y < 0))a.x = -a.x, a.y = -a.y;
	return a;
}
point Seg(point a, point b) {
	return { b.y - a.y, a.x - b.x, a.y*b.x - a.x*b.y };
}
point Cross(point a, point b) {
	return { a.y*b.z - b.y*a.z, a.z*b.x - b.z*a.x, a.x*b.y - a.y*b.x };
}
void Put(point &a, point &b, point &c, point &d) {
	point s1 = Seg(a, b), s2 = Seg(c, d);
	point p = Cross(s1, s2);
	if (!p.z || p.x%p.z || p.y%p.z)return;
	p.x /= p.z, p.y /= p.z;
	if (abs(p.x) > 1e6 || abs(p.y) > 1e6)return;
	Map[{p.x, p.y}]++;
}
bool SameLine(point &a, point &b) {
	return a.x*b.y == a.y*b.x;
}
bool Pos(point a) {
	int i;
	for (i = 1; i <= n; i++) {
		P[i] = To1(w[i] - a);
	}
	sort(P + 1, P + n + 1);
	int p1 = 0, p2 = 0;
	for (i = 1; i <= n; i += 2) {
		if (!SameLine(P[i], P[i + 1]))return false;
		if (i + 2 <= n && SameLine(P[i + 1], P[i + 2]))return false;
	}
	return true;
}
int O[5210];
int main() {
	int i, j;
	scanf("%d", &n);
	n *= 2;
	for (i = 1; i <= n; i++) {
		long long x, y;
		scanf("%lld%lld", &x, &y);
		Map[{x, y}] = -1e9;
		w[i] = point(x, y);
	}
	long long Mx = -1;
	int p1, p2;
	for (i = 1; i <= n; i++) {
		for (j = i + 1; j <= n; j++) {
			long long t = (w[j] - w[i]).SZ();
			if (Mx < t)Mx = t, p1 = i, p2 = j;
		}
	}
	swap(w[1], w[p1]);
	swap(w[2], w[p2]);
	for (i = 3; i <= n; i++) {
		for (j = i + 1; j <= n; j++) {
			Put(w[1], w[i], w[2], w[j]);
			Put(w[1], w[j], w[2], w[i]);
			Put(w[1], w[2], w[i], w[j]);
		}
	}
	int cnt = 0;
	for (auto &tp : Map) {
		if (tp.second < 0)continue;
		U[cnt++] = { tp.first,tp.second };
	}
	sort(U, U + cnt);
	for (i = cnt - 1; i >= cnt - 2500 && i >= 0; i--) {
		if (Pos(point(U[i].a.first, U[i].a.second))) {
			printf("Yes\n%lld %lld\n", U[i].a.first, U[i].a.second);
			return 0;
		}
	}
	printf("No\n");
}