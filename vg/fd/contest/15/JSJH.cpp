#include <cstdio>
#include <cmath>
#include <vector>
#include <cstring>
#include <iostream>
struct point {
  double x,y;
  point (double x=0,double y=0):x(x),y(y){}
};
typedef point Vector;
inline Vector operator + (const Vector &a, const Vector &b) {
  return Vector(a.x + b.x, a.y + b.y);
}
inline Vector operator - (const Vector &a, const Vector &b) {
  return Vector(a.x - b.x, a.y - b.y);
}
inline Vector operator * (const Vector &a, double t) {
  return Vector(a.x * t, a.y * t);
}
inline Vector operator / (const Vector &a, double p) {
  return Vector(a.x / p, a.y / p);
}
inline int sgn(double x,double eps=1e-8) {
  return x < -eps ? -1 : x > eps;
}
bool operator < (const point &a, const point &b) {
  return sgn(a.x - b.x) < 0 || sgn(a.x - b.x) == 0 && sgn(a.y - b.y) < 0;
}
bool operator == (const point &a, const point &b) {
  return sgn(a.x - b.x) == 0 && sgn(a.y - b.y) == 0;
}
inline double cross(Vector a, Vector b) {
  return a.x * b.y - a.y * b.x;
}
inline double dot(Vector a, Vector b) {
  return a.x * b.x + a.y * b.y;
}
point intersect(point P, Vector v, point Q, Vector w) {
  point p;
  Vector u = P - Q;
  double t = cross(w, u) / cross(v, w);
  p = P + v * t;
  return p;
}
int inhalfplane(point p,point s,point e) {
  return sgn(cross(e - s, p - s)) ;
}
std::vector<point> CUT(const std::vector<point> &p, point s, point e) {
  std::vector<point> q;
  int n = (int) p.size();
  for(int i = 0; i < n; i++) {
  	std::cout<<p[i].x<<" "<<p[i].y<<std::endl;
    int nowin = inhalfplane(p[i], s, e);
    int nextin = inhalfplane(p[(i + 1) % n], s, e);
    printf("zz%d %d\n",nowin,nextin);
    if(nowin >= 0) {
      q.push_back(p[i]);
    }
    if(nextin * nowin < 0) {
      q.push_back(intersect(p[i], p[(i + 1) % n] - p[i], s, e - s));
    }
  }
  return q;
}
double calc(const std::vector<point> &p) {
  int n = (int)p.size();
  double ans = 0;
  for(int i = 0; i < n; i++) {
  	std::cout<<p[i].x<<"zzzzz"<<p[i].y<<std::endl;
    ans += cross(p[i], p[(i + 1) % n]);
    std::cout<<"ans="<<ans<<std::endl;
  }
  return fabs(ans) / 2;
}
std::vector<point> convex[310];
double ret[310];
int main() {
  int n, k;
  while(scanf("%d%d",&n,&k)!=EOF) {
    for(int i = 0; i < k; i++) {
      ret[i] = 1000.0;
      convex[i].clear();
      convex[i].push_back(point(i, 0));
      convex[i].push_back(point(i + 1, 0));
      convex[i].push_back(point(i + 1, 1000));
      convex[i].push_back(point(i, 1000));
    }
    for(int i = 0; i < n; i++) {
      double y1, y2;
      scanf("%lf",&y1);
      double area = 0;
      for(int j = 0; j < k; j++) {
        scanf("%lf",&y2);
        convex[j] = CUT(convex[j], point(j, y1), point(j + 1, y2));
        double newarea = calc(convex[j]);
        area += ret[j] - newarea;
        ret[j] = newarea;
        y1 = y2;
      }
      printf("%.9f\n",area);
    }
  }
  return 0;
}
