#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
struct data{
  int nt, to;
  ll w;
}a[N];
queue<int>q;
int n, m, S, T, cnt = -1;
int head[N], dep[N], cur[N];
ll INF = 1e13, dis[N], Dis[N];

void add(int x,int y,int c){
  // printf("%d %d %d\n", x, y, c);
  a[++cnt].to=y,a[cnt].w=c,a[cnt].nt=head[x],head[x]=cnt;
  a[++cnt].to=x,a[cnt].w=0,a[cnt].nt=head[y],head[y]=cnt;
}

bool bfs() {
  memset(dep, 0, sizeof dep);
  q.push(S), dep[S] = 1;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(int i = head[u]; ~i; i = a[i].nt) {
      int to = a[i].to;
      if(!dep[to] && a[i].w) {
        dep[to] = dep[u] + 1;
        q.push(to);
      }
    }
  }
  return dep[T];
}

ll dfs(int s, ll v) {
  if(s == T) return v;
  for(int& i = cur[s]; ~i; i = a[i].nt) {
    if(dep[a[i].to] == dep[s] + 1 && a[i].w) {
      ll d = dfs(a[i].to, min(a[i].w, v));
      if(d) {
        a[i].w -= d;
        a[i ^ 1].w += d;
        return d;
      }
    }
  }
  return 0ll;
}

int main() {
  while(scanf("%d%d", &n, &m) == 2) {
    ll ans = 0;
    cnt = -1;
    for(int i = 1; i <= n + 2; ++i) {
      dis[i] = Dis[i] = 0;
      head[i] = -1;
    }
    for(int i = 1; i <= m; ++i) {
      int u, v, a, b, c;
      scanf("%d%d%d%d%d", &u, &v, &a, &b, &c);
      ans += a + b + c;
      dis[u] += b + c, dis[v] += b + c;
      Dis[u] += a + b, Dis[v] += a + b;
      add(u, v, a + c - 2 * b);
      add(v, u, a + c - 2 * b);
    }
    S = n + 1, T = n + 2;
    for(int i = 1; i <= n; ++i) {
      add(S, i, dis[i]);
      add(i, T, Dis[i]);
    }
    // printf("!!! %lld\n", ans);
    int pos = 0;
    for(; bfs();) {
      for(int i = 1; i <= n + 2; ++i)
        cur[i] = head[i];
      for(;ll d = dfs(S, INF);) 
        ans -= d / 2, pos += (d & 1);
    }
    printf("%lld\n", ans - pos / 2);
  }
}