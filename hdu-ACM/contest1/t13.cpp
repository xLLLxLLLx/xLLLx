#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110;

struct Point;
typedef Point Vector;
struct Point {
    ll x, y;
    void in() {
        scanf("%lld%lld", &x, &y);
    }
    Point() {
        x = 0, y = 0;
    }
    Point(int _x, int _y) {
        x = _x, y = _y;
    }
    Point operator + (Point C) {
        return Point(x + C.x, y + C.y);
    }
    Point operator - (Point C) {
        return Point(x - C.x, y - C.y);
    }
    ll dot(const Vector &a) {
        return x * a.x + y * a.y;
    }
    bool operator == (const Point &a) const {
        return x == a.x && y == a.y;
    }
    bool operator < (const Point &a) const {
        return (x < a.x) || x == a.x && y < a.y;
    }

};


struct Convex_Hull {
    Point p[2 * N];
    int n;
    void init() {
        n = 0;
    }
    void in() {
        p[n].in();
        n++;
    }
    inline void push_back(const Point &np) {
        p[n++] = np;
    }
    void gao() {
        if(n < 3) {
            return ;
        }
        std::sort(p, p + n);
        std::copy(p, p + n - 1, p + n);
        std::reverse(p + n, p + 2 * n - 1);
        int m = 0, top = 0;
        for(int i = 0; i < 2 * n - 1; i++) {
            while(top >= m + 2 && sgn((p[top - 1] - p[top - 2]) * (p[i] - p[top - 2])) <= 0) {
                top --;
            }
            p[top++] = p[i];
            if(i == n - 1) {
                m = top - 1;
            }
        }
        n = top - 1;
    }
    void print() {
        for(int i = 0; i < n; i++) {
            p[i].print();
        }
    }
    double get_area() {
        double ret = 0;
        Point ori(0, 0);
        for(int i = 0; i < n; i++) {
            ret += (p[i] - ori) * (p[i + 1] - ori);
        }
        return fabs(ret) / 2;
    }
    double rotate() {
        if(n == 2) {
            return (p[0] - p[1]).dot(p[0] - p[1]);
        }
        int i = 0, j = 0;
        for(int k = 0; k < n; k++) {
            if(!(p[k] < p[i])) i = k;
            if(!(p[j] < p[k])) j = k;
        }
        double ret = 0;
        int si = i, sj = j;
        while(i != sj || j != si) {
            ret = std::max(ret, (p[i]-p[j]).dot(p[i]-p[j]));
            if(sgn ( (p[(i + 1) % n] - p[i]) * (p[(j + 1) % n] - p[j]) ) < 0) {
                i = (i + 1) % n;
            } else {
                j = (j + 1) % n;
            }
        }
        return ret;
    }
    bool in_convex(Point pt) {
        if(sgn((p[1]-p[0])*(pt-p[0])) <= 0 || sgn((p[n-1]-p[0])*(pt-p[0])) >= 0) {
            return false;
        }
        int l = 1, r = n - 2, best = -1;
        while(l <= r) {
            int mid = l + r >> 1;
            int f = sgn((p[mid] - p[0]) * (pt - p[0]));
            if(f >= 0) {
                best = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        return (p[best+1] - p[best]) * (pt - p[best]) > 0;
    }

}convex;
