#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1010;
struct data {
  int nt, to, w;
} a[N * N * 2][2];
int head[N][2], cnt[2];

void add(int x, int y, int w, int id) {
  a[++cnt[id]][id].to = y;
  a[cnt[id]][id].w = w;
  a[cnt[id]][id].nt = head[x][id];
  head[x][id] = cnt[id];
}

int n, m, s, t;

ll dis[N];
typedef pair<ll, int> P;
priority_queue<P, vector<P>, greater<P> >q;

void dij(int st, int id) {
  memset(dis, 0x3f, sizeof dis);
  dis[st] = 0;
  q.push(P(0, st));
  while(!q.empty()) {
    P h = q.top(); q.pop();
    int u = h.second;
    ll w = h.first;
    if(dis[u] < w) continue;
    // printf("%d %lld\n", u, w);
    for(int i = head[u][id]; i; i = a[i][id].nt) {
      int to = a[i][id].to;
      if(dis[to] > w + a[i][id].w) {
        dis[to] = w + a[i][id].w;
        q.push(P(dis[to], to));
      }
    }
  }
  /*for(int i = 1; i <= n; ++i)
    printf("%lld ", dis[i]);
  puts("");*/
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    cnt[0] = cnt[1] = 0;
    scanf("%d%d%d%d", &n, &m, &s, &t);
    for(int i = 1; i <= n; ++i)
      head[i][0] = head[i][1] = 0;
    for(int i = 1, x, y, z; i <= m; ++i) {
      scanf("%d%d%d", &x, &y, &z);
      add(x, y, z, 0), add(y, x, z, 0);
    }
    for(int i = 1, x, y; i <= n; ++i) {
      scanf("%d%d", &x, &y);
      // puts("xxX");
      dij(i, 0);
      // puts("XXXXX");
      for(int j = 1; j <= n; ++j) {
        if(i != j && dis[j] <= x) {
          add(i, j, y, 1);
        }
      }
    }
    dij(s, 1);
    if(dis[t] != dis[0]) printf("%lld\n", dis[t]);
    else printf("-1\n");
  }
  return 0;
}

/*
1
4 4
1 3
1 2 3
1 4 1
2 4 1
2 3 5
2 7
7 2
1 2
7 7

9
*/