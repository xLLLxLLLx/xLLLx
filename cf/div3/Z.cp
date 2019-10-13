#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 310;
struct data {
  int nt, to, w;
} a[N * N];
int head[N], cnt = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].w = w;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

ll ans = 0;

typedef pair<int, int> P;
priority_queue<P, vector<P>, greater<P> > q;
int dis[N];

void dij(int stop, int x) {
  memset(dis, 0x3f, sizeof dis);
  dis[x] = 0, q.push(P(0, x));
  while(!q.empty()) {
    P h = q.top(); q.pop();
    int d = h.first, now = h.second;
    if(d > dis[now]) continue;
    for(int i = head[now]; i; i = a[i].nt) {
      int to = a[i].to;
      if(to == stop) continue;
      if(dis[to] > dis[now] + a[i].w) {
        dis[to] = dis[now] + a[i].w;
        q.push(P(dis[to], to));
      }
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      int x; scanf("%d", &x);
      if(x != -1 && i != j) add(i, j, x);
    }
  }
  for(int i = 1; i <= n; ++i) {
    for(int j = 1; j <= n; ++j) {
      if(i == j) continue;
      dij(i, j);
      for(int k = 1; k <= n; ++k)
        if(k != i) {
          if(dis[k] == dis[0]) ans--;
          else ans += dis[k];
        }
    }
  }
  printf("%lld\n", ans);
  return 0;
}