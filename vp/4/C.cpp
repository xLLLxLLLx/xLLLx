#include <bits/stdc++.h>
using namespace std;
const double eps = 1e-3;
const int N = 110;
int f[N], sz[N];
double R[N];

int sgn(double x) {
  return x < -eps ? -1 : x > eps;
}
int find(int k) {
  return f[k] == k ? f[k] : f[k] = find(f[k]);
}
struct Point;
typedef Point Vector;
struct Point {
  double x, y;
  Point() {x = 0, y = 0; }
  Point(double _x, double _y) { x = _x, y = _y; }
  double dot(const Vector &a) {
    return x * a.x + y * a.y;
  }
  Vector operator + (const Vector &a) const {
    return Vector(x + a.x, y + a.y);
  }
  Vector operator - (const Vector &a) const {
    return Vector(x - a.x, y - a.y);
  }
  double operator * (const Vector &a) const {
    return x * a.y - y * a.x;
  }
  Vector operator * (double t) const {
    return Vector(x * t, y * t);
  }
  bool operator == (const Point &a) const {
    return sgn(x - a.x) == 0 && sgn(y - a.y) == 0;
  }
  bool operator < (const Point &a) const {
    return sgn(x - a.x) < 0 || sgn(x - a.x) == 0 && sgn(y - a.y) < 0;
  }
} z[N * N * 2], a[N], jiao[N][N << 1];

double cross(Point a, Point b, Point c) {
  return (b.x - a.x) * (c.y - a.y) - (c.x - a.x) * (b.y - a.y);
}

double ppdis(Point a, Point b) {
  return sqrt((a - b).dot(a - b));
}

double pldis(Point p, Point l1, Point l2) {
  return fabs(cross(p, l1, l2)) / ppdis(l1, l2);
}

bool cir_line(Point ct, double r, Point l1, Point l2, Point& p1, Point& p2) {
  if ( sgn (pldis(ct, l1, l2) - r ) > 0)
    return false;
  double a1, a2, b1, b2, A, B, C, t1, t2;
  a1 = l2.x - l1.x; a2 = l2.y - l1.y;
  b1 = l1.x - ct.x; b2 = l1.y - ct.y;
  A = a1 * a1 + a2 * a2;
  B = (a1 * b1 + a2 * b2) * 2;
  C = b1 * b1 + b2 * b2 - r * r;
  double delta = fabs(B * B - 4.0 * A * C);
  t1 = (-B - sqrt(delta)) / 2.0 / A;
  t2 = (-B + sqrt(delta)) / 2.0 / A;
  p1.x = l1.x + a1 * t1; p1.y = l1.y + a2 * t1;
  p2.x = l1.x + a1 * t2; p2.y = l1.y + a2 * t2;
  return true;
}

bool cir_cir(Point c1, double r1, Point c2, double r2, Point& p1, Point& p2) {
  double d = ppdis(c1, c2);
  if ( sgn(d - r1 - r2) > 0|| sgn (d - fabs(r1 - r2) ) < 0 )
    return false;
  Point u, v;
  double t = (1 + (r1 * r1 - r2 * r2) / ppdis(c1, c2) / ppdis(c1, c2)) / 2;
  u.x = c1.x + (c2.x - c1.x) * t;
  u.y = c1.y + (c2.y - c1.y) * t;
  v.x = u.x + c1.y - c2.y;
  v.y = u.y + c2.x - c1.x;
  cir_line(c1, r1, u, v, p1, p2);
  return true;
}

int main() {
  freopen("circles.in", "r", stdin);
  freopen("circles.out", "w", stdout);
  int n, cnt = 0;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    f[i] = i;
    scanf("%lf%lf%lf", &a[i].x, &a[i].y, &R[i]);
  }
  int edge = 0;
  for(int i = 1; i <= n; ++i) {
    for(int j = i + 1; j <= n; ++j) {
      Point p1, p2;
      if(cir_cir(a[i], R[i], a[j], R[j], p1, p2)) {
        int fx = find(i), fy = find(j);
        f[fx] = fy;
        z[++cnt] = p1, z[++cnt] = p2;
        jiao[i][++sz[i]] = p1, jiao[i][++sz[i]] = p2;
        jiao[j][++sz[j]] = p1, jiao[j][++sz[j]] = p2;
      }
    }
  }
  for(int i = 1; i <= n; ++i) {
    sort(jiao[i] + 1, jiao[i] + 1 + sz[i]);
    edge += (sz[i] > 1);
    for(int j = 2; j <= sz[i]; ++j) {
      if(jiao[i][j] == jiao[i][j - 1]) {
        continue;
      }
      edge++;
    }
  }
  sort(z + 1, z + 1 + cnt);
  int num = (cnt >= 1);
  // printf("%.2f %.2f\n", z[1].x, z[1].y);
  for(int i = 2; i <= cnt; ++i) {
    // printf("%.2f %.2f\n", z[i].x, z[i].y);
    if(z[i] == z[i - 1]) {
      continue;
    }
    num++;
  }
  int block = 0;
  for(int i = 1; i <= n; ++i) {
    block += (find(i) == i);
  }
  // printf("%d %d %d\n", block, num, edge);
  printf("%d\n", block + 1 - num + edge);
  return 0;
}