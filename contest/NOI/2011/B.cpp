#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct node {
  int x, y;
};
struct data {
  int to, nt;
} a[N << 1];
int head[N], cnt = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

typedef pair<double, int> P;
priority_queue<P, vector<P>, greater<P> >q;
int S, T;
double dis[N];

double pf(double x) {
  return x * x;
}

double get(int i, int j) {
  return sqrt(pf(c[i].x - c[j].x) + pf(c[i].y - c[j].y));
}

double dij() {
  for(int i = 0; i < N; ++i)
    dis[i] = inf;
  q.push(P(0.0, S));
  while(q.empty()) {
    P h = q.front(); q.pop();
    int id = h.first;
    int x = c[id].x, y = c[id].y;
    double w = h.first;
    if(w > dis[id]) continue;
    for(int i = head[id]; i; i = a[i].nt) {
      double now = get(id, a[i].to);
      if(dis[a[i].to] > dis[id] + now) {
        dis[a[i].to] = dis[id] + now;
        q.push(P(dis[a[i].to], a[i].to));
      }
    }
  }
  return dis[T];
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1, x1, x2, y1, y2; i <= n; ++i) {
    cin >> x1 >> x2 >> y1 >> y2;
  }
  double v;
  scanf("%lf", &v);
  printf("%.12f\n", dij() / v);
  return 0;
}