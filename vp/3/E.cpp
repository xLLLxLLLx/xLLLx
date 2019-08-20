#include <bits/stdc++.h>
using namespace std;
const int N = 410;
struct data {
  int nt, to;
} a[N * N];
int n, m, S, T;
vector<int> g[N];
int head[N], dis[N], cnt = 1;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

typedef pair<int, int> P;
priority_queue<P, vector<P>, greater<P> > q;
void dij() {
  dis[T] = 0;
  q.push(P(dis[T], T));
  while(!q.empty()) {
    P h = q.top(); q.pop();
    if(h.first > dis[h.second]) continue;
    for(int i = head[h.second]; i; i = a[i].nt) {
      int to = a[i].to;
      if(h.first + 1 < dis[to]) {
        dis[to] = h.first + 1;
        q.push(P(dis[to], to));
      }
    }
  }
  for(int i = 1; i <= n; ++i)
    for(int j = head[i]; j; j = a[j].nt) {
      int to = a[j].to;
      if(dis[to] == dis[i] + 1) {
        g[dis[to]].push_back(j >> 1);
      }
    }
}

int main() {
  freopen("defence.in", "r", stdin);
  freopen("defence.out", "w", stdout);
  scanf("%d%d%d%d", &n, &m, &S, &T);
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  memset(dis, 0x3f, sizeof dis);
  dis[T] = 0;
  dij();
  if(dis[S] != dis[0]) {
    printf("%d\n", dis[S]);
    for(int i = 1; i <= dis[S]; ++i) {
      printf("%d ", g[i].size());
      for(int j = 0; j < g[i].size(); ++j)
        printf("%d ", g[i][j]);
      puts("");
    }
  } else {
    printf("%d\n", m);
    for(int i = 1; i <= m; ++i) {
      printf("1 %d\n", i);
    }
  }
  return 0;
}