#include <bits/stdc++.h>
using namespace std;
 
const int N = 100010;
 
const double eps = 1e-12;
const double pi = acos(-1.0);
 
int sgn(double x) {
    return x < -eps ? -1 : x > eps;
}
struct Point;
typedef Point Vector;
struct Point 
{
    double x, y;
    void in() {
        scanf("%lf%lf", &x, &y);
    }
    void print() {
        printf("%.2lf %.2lf\n", x, y);
    }
    Point(double x = 0, double y = 0) : x(x), y(y) {
    }
    inline Vector rotate(double ang) {
        return Vector(x * cos(ang) - y * sin(ang), x * sin(ang) + y * cos(ang));
    }
    inline double dot(const Vector &a) {
        return x * a.x + y * a.y;
    }
    inline bool operator == (const Point &a) const {
        return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
    }
    inline bool operator < (const Point &a) const {
        return sgn(x - a.x) < 0 ||sgn(x - a.x) == 0 && sgn(y - a.y) < 0;
    }
    inline Vector operator + (const Vector &a) const {
        return Vector(x + a.x, y + a.y);
    }
    inline Vector operator - (const Vector &a) const {
        return Vector(x - a.x, y - a.y);
    }
    inline double operator * (const Vector &a) const {
        return x * a.y - y * a.x;
    }
    inline Vector operator * (double t) const {
        return Vector(x * t, y * t);
    }
    inline Vector operator / (double t) {
        return Vector(x / t, y / t);
    }
    inline double vlen() {
        return sqrt(x * x + y * y);
    }
    inline Vector norm() {
        return Point(-y, x);
    }
 
}p[N];
 
struct  Event {
    double l, r;
    int tp;
    Event(double l=0,double r=0,int tp=0):l(l), r(r), tp(tp) {
    }
    bool operator < (const Event& cmp) const {
        return tp == cmp.tp ? sgn(r-cmp.r)<0 : tp < cmp.tp;
    }
};
 
int n, m;
int dp[20][N << 1];
 
bool judge(double mid) {
    vector <Event> e;
    for (int i = 0; i < n; i++) {
        double ang = atan2(p[i].y, p[i].x), delta = acos(mid / p[i].vlen());
        double l = ang - delta;
        double r = ang + delta;
        while (l < 0 || r < 0) {
            l += 2.0 * pi;
            r += 2.0 * pi;
        }
 
        while (r >= 2 * pi) {
            r -= 2.0 * pi;
            l -= 2.0 * pi;
        }
        e.push_back(Event(l, r, 0));
        e.push_back(Event(l + 2*pi, r + 2*pi, 1));
    }
    sort (e.begin(), e.end());
    int tot = n << 1;
    int pt = 0;
    for (int i = 0; i < tot; i++) {
      // cout << "point" << e[i].l << " " << e[i].r << endl;
        while (pt < tot && sgn(e[pt].l - e[i].r) <= 0) {
            pt++;
        }
        dp[0][i] = pt;
        //cout << i << " " << pt <<endl;
    }
 
    for (int j = 1; j < 20; j++) {
        for (int i = 0; i < tot; i++) {
            dp[j][i] = dp[j-1][dp[j-1][i]];
        }
    }
    for (int start = 0; start < n; start++) {
        int now = start;
        int cnt = 0;
        for (int i = 19; i >= 0; i--) if (m >> i & 1) {
            now = dp[i][now];
            if (now == 0) {
                break;
            }
        }
        //cout << start << " " << now <<endl;
        if (now == 0 || now >= start + n) {
            return true;
        }
    }
    return false;
}
int main() {
    scanf("%d%d", &n, &m);
    double l = 0, r = 1e50;
    for (int i = 0; i < n; i++) {
        p[i].in();
        r = min(r, p[i].vlen());
    }
    if (m >= n) {
        printf("%.9f\n", r);
        return 0;
    }
    for(int i = 1; i <= 100; ++i) {
        double mid = (l + r) * 0.5;
        if (judge(mid)) {
            l = mid;
        } else {
            r = mid;
        }
        if(fabs(l - r) <= eps) break;
    }
    printf("%.9f\n",l);
    return 0;
}