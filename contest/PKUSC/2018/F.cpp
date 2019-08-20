#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-8, PI = acos(-1.0);
const int N = 510;
double ans = 0.0;

bool dcmp(double A, double B) {
	return fabs(A - B) < eps;
}

struct Point {
	double x, y;
	Point(double _x = 0, double _y = 0) {
		x = _x, y = _y;
	}
	friend Point operator + (const Point &A, const Point &B) {
		return Point(A.x + B.x, A.y + B.y);
	}
	friend Point operator - (const Point &A, const Point &B) {
		return Point(A.x - B.x, A.y - B.y);
	}
	friend Point operator * (const Point &A, double &d) {
		return Point(A.x * d, A.y * d);
	}
	friend Point operator / (const Point &A, double &d) {
		return Point(A.x / d, A.y / d);
	}
	friend double operator * (const Point & A, const Point &B) {
		return A.x * B.y - A.y * B.x;
	}
	friend double dot(const Point &A, const Point &B) {
		return A.x * B.x + A.y * B.y;
	}
	double dis() {
		return sqrt(x * x + y * y);
	}
} P[N], conv[N];

void Calc(Point A, Point B, double R) {
	double f = 1;
	if(A * B < 0) f = -1;
	if(max(A.dis(), B.dis()) < R) return ;
	double theta = acos(dot(A, B) / (A.dis() * B.dis()));
	double h = fabs(A * B) / (B - A).dis();
	if(h >= R) {
		ans += f * theta;
		return ;
	}
	double beta = acos(dot(A - B, Point(-B.x, -B.y)) / ((A - B).dis() * B.dis()));
	double alpha = acos(dot(B - A, Point(-A.x, -A.y)) / ((A - B).dis() * A.dis()));
	double t = asin(h / R);
	double s = 0.0;
	if(t > alpha) s += t - alpha;
	if(t > beta) s += t - beta;
	s = min(s, theta);
	ans += f * s;
}

bool check(Point A, Point B) {
	Point C(1, 0);
	if(A.y < B.y) swap(A, B);
	return C * A > 0 && B * C > 0 && B * A > 0;
}

int main() {
	int n, m;
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) 
		scanf("%lf%lf", &P[i].x, &P[i].y);
	for(int i = 1; i <= m; ++i)
		scanf("%lf%lf", &conv[i].x, &conv[i].y);
	conv[m + 1] = conv[1];
	for(int i = 1; i <= m; ++i) {
		if(!dcmp(conv[i] * conv[i + 1], 0)) {
			for(int j = 1; j <= n; ++j) {
				if(!dcmp(P[j].dis(), 0.0))
					Calc(conv[i], conv[i + 1], P[j].dis());
			}
		}
	}
	for(int j = 1; j <= n; ++j) {
		if(dcmp(P[j].dis(), 0)) {
			int flg = 1, t = 0;
			for(int i = 1; i <= m; ++i) {
				if(dcmp((conv[i] - P[j]) * (conv[i + 1] - P[j]), 0)) {
					if(dot((conv[i] - P[j]), (conv[i + 1] - P[j])) <= 0) {
						flg = 0;
						break;
					}
				} else {
					if(dcmp(conv[i].y, 0)) {
						if(conv[i].x > 0) ++t;
					} else {
						t += check(conv[i], conv[i + 1]);
					}
				}
			}
			if(flg && (t & 1)) 
				ans += 2.0 * PI;
		}
	}
	ans /= PI * 2.0;
	printf("%.5f\n", ans);
	return 0;
}