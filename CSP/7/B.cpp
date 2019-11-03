#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data {
  int nt, to;
} a[N << 1];
int head[N], cnt = 0, res = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void dfs(int u, int fa) {
  dfn[u] = ++res;
  dep[u] = dep[fa] + 1;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }

  return 0;
}