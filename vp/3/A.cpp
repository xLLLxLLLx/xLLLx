#include <bits/stdc++.h>
using namespace std;
const int N = 2e4 + 10;
const double eps = 1e-8;

struct point {
  double x, y;
  point(){}
  point(double _x, double _y) {
    x = _x, y = _y;
  }
  friend point operator + (const point &a, const point &b) {
    return point(a.x + b.x, a.y + b.y);
  }
  friend point operator - (const point &a, const point &b) {
    return point(a.x - b.x, a.y - b.y);
  }
  friend point operator * (const point &a, const double &b) {
    return point(a.x * b, a.y * b);
  }
  friend double operator * (const point &a, const point &b) {
    return a.x * b.x + a.y * b.y;
  }
  friend double operator ^ (const point &a, const point &b) {
    return a.x * b.y - a.y * b.x;
  }
  friend bool operator < (const point &a, const point &b) {
    return a.x - b.x < -eps || (abs(a.x - b.x) < eps && a.y - b.y < -eps);
  }
  friend bool operator == (const point &a, const point &b) {
    return abs(a.x - b.x) < eps && abs(a.y - b.y) < eps;
  }
  double len() {
    return sqrt(x * x + y * y);
  }
  point unit() {
    double d = len();
    return point(x / d,y / d);
  }
  double ang() {
    return atan2(y, x);
  }
};

struct line {
  point st, ed, v;
} l[N];
vector<point> p;
vector<double> ans;
int n, cnt = -1;
int head[N], nt[N], nte[N], to[N], vis[N];

point get(line a, line b) {
  double s1 = b.v ^ (a.st - b.st);
  double s2 = ((a.ed - b.st) ^ b.v) + s1;
  return a.st + a.v * (s1 / s2);
}

int getid(const point &a) {
  return lower_bound(p.begin(), p.end(), a) - p.begin();
}

void add(int x, int y) {
  to[++cnt] = y;
  nt[cnt] = head[x];
  head[x] = cnt;
}

typedef pair<double, int> mp;

void prepare() {
  scanf("%d", &n);
  for(int i = 0; i < n; ++i) {
    scanf("%lf%lf%lf%lf", &l[i].st.x, &l[i].st.y, &l[i].ed.x, &l[i].ed.y);
    l[i].v = l[i].ed - l[i].st;
  }
  for(int i = 0; i < n; ++i)
    for(int j = i + 1; j < n; ++j) {
      if(abs(l[i].v ^ l[j].v) > eps) 
        p.push_back(get(l[i], l[j]));
    }
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());
  for(int i = 0; i < n; ++i) {
    vector<double> dis;
    point d = l[i].v.unit();
    for(int j = 0; j < n; ++j) {
      if(abs(l[i].v ^ l[j].v) > eps) {
        point now = get(l[i], l[j]);
        dis.push_back((now - l[i].st) * d);
      }
    }
    sort(dis.begin(), dis.end());
    dis.erase(unique(dis.begin(), dis.end()), dis.end());
    for(int j = 1; j < dis.size(); ++j) {
      int A = getid(l[i].st + d * dis[j]);
      int B = getid(l[i].st + d * dis[j - 1]);
      add(A, B), add(B, A);
    }
  }
  // printf("tot=%d\n", p.size());
  for(int i = 0; i < p.size(); ++i) {
    // printf("%d\n", i);
    vector<mp> P;
    for(int e = head[i]; ~e; e = nt[e]) {
      P.push_back(mp((p[to[e]] - p[i]).ang(), e));
    }
    sort(P.begin(), P.end());
    // puts("hello");
    int gg = P.size();
    for(int j = 0; j < gg; ++j) {
      nte[P[(j + 1) % gg].second ^ 1] = P[j].second;
    }
  }
  // puts("XXXX");
}

void go() {
  for(int i = 0; i <= cnt; ++i) {
    if(vis[i]) continue;
    stack<int> s;
    s.push(i), vis[i] = 1;
    int j = nte[i];
    while(!vis[j]) {
      if(!s.empty() && (s.top() ^ 1) == j) s.pop();
      else s.push(j);
      vis[j] = 1;
      j = nte[j];
      if(j == -1) break;
    }
    if(i == j) {
      double area = 0;
      while(!s.empty()) {
        area += (p[to[s.top() ^ 1]] ^ p[to[s.top()]]);
        s.pop();
      }
      area /= 2.0;
      if(area > 0) ans.push_back(area);
    }
  }
}

int main() {
  freopen("areas.in", "r", stdin);
  freopen("areas.out", "w", stdout);
  memset(head, -1, sizeof head);
  memset(nte, -1, sizeof nte);
  prepare(), go();
  sort(ans.begin(), ans.end());
  printf("%d\n", (int)ans.size());
  for(int i = 0; i < ans.size(); ++i) {
    printf("%.4f\n", ans[i]);
  }
  return 0;
}