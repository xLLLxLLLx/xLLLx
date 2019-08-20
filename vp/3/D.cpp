#include <bits/stdc++.h>
using namespace std;
const int N = 1510, M = 3e5 + 10, inf = 1e9;
struct data {
  int nt, to, w;
} a[M << 1];
int n, m, L;
int S, T;
int head[N], f[N], level[N], cnt = -1;
 
void add(int x, int y, int w) {
  a[++cnt].to = y;
  a[cnt].w = w;
  a[cnt].nt = head[x];
  head[x] = cnt;
}
 
int out[N], in[N];
 
bool cmp(int x, int y) {
  return level[x] < level[y];
}
 
void prepare() {
  sort(f + 1, f + 1 + n, cmp);
  memset(in, 0, sizeof in);
  memset(out, 0, sizeof out);
  in[S] = inf;
  for(int o = 1; o <= n; ++o) {
    int u = f[o];
    for(int i = head[u]; ~i; i = a[i].nt) {
      int to = a[i].to, w = a[i].w;
      if(i % 2 == 0 && in[u] > out[u]) {
        int f = min(w, in[u] - out[u]);
        in[to] += f, out[u] += f;
      }
    }
  }
  memset(in, 0, sizeof in);
  in[T] = inf;
  for(int o = n; o >= 1; --o) {
    int u = f[o];
    for(int i = head[u]; ~i; i = a[i].nt) {
      int to = a[i].to, w = a[i ^ 1].w;
      if((i & 1) && out[to] > in[to]) {
        int f = min(w, min(out[to] - in[to], in[u]));
        in[to] += f, in[u] -= f;
        a[i].w += f, a[i ^ 1].w -= f;
      }
    }
  }
}
 
int dep[N], cur[N];
queue<int> q;
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
 
int dfs(int s, int v) {
  if(s == T) return v;
  for(int& i = cur[s]; ~i; i = a[i].nt) {
    if(dep[a[i].to] == dep[s] + 1 && a[i].w) {
      int d = dfs(a[i].to, min(a[i].w, v));
      if(d) {
        a[i].w -= d;
        a[i ^ 1].w += d;
        return d;
      }
    }
  }
  return 0ll;
}
 
void Dinic() {
  for(; bfs();) {
    for(int i = 1; i <= n; ++i)
      cur[i] = head[i];
    for(; dfs(S, inf);) ;
  }
}
 
int main() {
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
  memset(head, -1, sizeof head);
  scanf("%d%d%d", &n, &m, &L);
  for(int i = 1; i <= n; ++i) f[i] = i;
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &level[i]);
    if(level[i] == 1) S = i;
    if(level[i] == L) T = i;
  }
  for(int i = 1, x, y, w; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &w);
    add(x, y, w);
    add(y, x, 0);
  }
  prepare();
  Dinic();
  for(int i = 1; i <= m; ++i) {
    printf("%d\n", a[(i << 1) - 1].w);
  }
  return 0;
}