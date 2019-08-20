#include <bits/stdc++.h>
using namespace std;
const int M = 1e4 + 10, N = 810, inf = 1e9;
struct data {
  int nt, to, w;
} a[M << 2];
int n, m, S, T;
int head[N], cnt = -1;

void add(int x, int y, int w) {
  a[++cnt].to = y;
  a[cnt].w = w;
  a[cnt].nt = head[x];
  head[x] = cnt;
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

int vis[N];

int main() {
  freopen("attack.in", "r", stdin);
  freopen("attack.out", "w", stdout);
  memset(head, -1, sizeof head);
  scanf("%d%d%d%d", &n, &m, &S, &T);
  for(int i = 1, x, y, w; i <= m; ++i) {
    scanf("%d%d%d", &x, &y, &w);
    add(x, y, w), add(y, x, 0);
    add(y, x, w), add(x, y, 0);
  }
  for(; bfs(); ) {
    for(int i = 1; i <= n; ++i)
      cur[i] = head[i];
    for(; dfs(S, inf); );
  }
  q.push(S), vis[S] = 1;
  while(!q.empty()) {
    int h = q.front(); q.pop();
    for(int i = head[h]; ~i; i = a[i].nt) {
      int to = a[i].to;
      if(a[i].w > 0) {
        if(!vis[to]) {
          vis[to] = 1;
          q.push(to);
        }
      }
    }
  }
  q.push(T), vis[T] = 1;
  while(!q.empty()) {
    int h = q.front(); q.pop();
    for(int i = head[h]; ~i; i = a[i].nt) {
      int to = a[i].to;
      if(a[i ^ 1].w > 0) {
        if(!vis[to]) {
          vis[to] = 1;
          q.push(to);
        }
      }
    }
  }
  // for(int i = 1; i <= n; ++i)
  //   for(int j = head[i]; ~j; j = a[j].nt)
  //     printf("%d %d %d\n", i, a[j].to, a[j].w);
  for(int i = 1; i <= n; ++i)
    if(!vis[i]) return printf("AMBIGUOUS\n"), 0;
  printf("UNIQUE\n");
  return 0;
}