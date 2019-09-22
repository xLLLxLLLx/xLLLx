#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5010;
struct data {
  int x, y, id;
} a[N];
int cnt = 0, now = 1, k = 1;
int head[N], d[N], vis[N];

void add(int x, int y, int id) {
  a[++cnt].to = y;
  a[cnt].id = id;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void dfs(int x) {
  vis[x] = 1;
  for(int i = head[x]; i; i = a[i].nt) {
    int to = a[i].to;
    if(vis[to] != 1) d[a[i].id] = now;
    else {
      ++k;
      d[a[i].id] = 3 - now;
    }
    if(!vis[to]) dfs(to);
  }
  vis[x] = 2;
}

int main() {
  int n, m;
  scnaf("%d%d", &n, &m);
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y, i);
  }
  for(int i = 1; i <= n; ++i) {
    if(!vis[i]) {
      dfs(i);
    }
  }
  printf("%d\n", now);
  for(int i = 1; i <= m; ++i) {
    printf("%d ", d[i]);
  }
  return 0;
}