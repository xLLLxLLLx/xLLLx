#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
struct data {
  int nt, to;
} a[N << 1];
int n, m;
int head[N], cnt = 0;
int col[N], zx[N], st[N], top = 0, sz = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void dfs(int u, int fa) {
  int lst = top;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    dfs(to, u);
    if(top - lst >= m) {
      zx[++sz] = u;
      while(top > lst) 
        col[st[top--]] = sz;
    }
  }
  st[++top] = u;
}

int main() {
  freopen("royal.in", "r", stdin);
  freopen("royal.out", "w", stdout);
  scanf("%d%d", &n, &m);
  if(n == m) {
    printf("1\n");
    for(int i = 1; i <= n; ++i) printf("1 ");
    printf("\n1\n");
    return 0;
  }
  for(int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  dfs(1, 0);
  while(top) col[st[top--]] = sz;
  for(int i = 1; i <= n; ++i)
    if(!col[i]) return printf("0\n"), 0;
  printf("%d\n", sz);
  for(int i = 1; i <= n; ++i)
    printf("%d ", col[i]);
  puts("");
  for(int i = 1; i <= sz; ++i)
    printf("%d ", zx[i]);
  return 0;
}