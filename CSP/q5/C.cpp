#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct data { 
  int nt, to;
} a[N << 1];
vector<int> g[N];
int head[N], st[N], ed[N], n, cnt = 0;

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

int tag[N << 2], sum[N << 2], mn[N << 2], num[N << 2];

#define ls x << 1
#define rs x << 1 | 1

void up(int x) {
  sum[x] = sum[ls] + sum[rs];
  if(mn[ls] < mn[rs]) {
    mn[x] = mn[ls];
    num[x] = num[ls];
  } else if(mn[rs] < mn[ls]) {
    mn[x] = mn[rs];
    num[x] = num[rs];
  } else {
    mn[x] = mn[ls];
    num[x] = num[ls] + num[rs];
  }
}

void down(int x) {
  if(tag[x]) {
    if(mn[ls]) sum[ls] -= num[ls];
    mn[ls] += tag[x];
    if(mn[ls]) sum[ls] += num[ls];
    if(mn[rs]) sum[rs] -= num[rs];
    mn[rs] += tag[x];
    if(mn[rs]) sum[rs] += num[rs];
    tag[ls] += tag[x];
    tag[rs] += tag[x];
    tag[x] = 0;
  }
}

void build(int x, int l, int r) {
  if(l == r) {
    sum[x] = tag[x] = mn[x] = 0;
    num[x] = 1;
    return ;
  }
  int mid = (l + r) >> 1;
  build(ls, l, mid), build(rs, mid + 1, r);
  up(x);
  // printf("qwqx = %d mn = %d num = %d sum = %d\n", x, mn[x], num[x], sum[x]);
}

void upd(int x, int l, int r, int L, int R, int w) {
  if(L > R) return ;
  // printf("%d %d %d %d %d %d\n", x, l, r, L, R, w);
  if(L <= l && r <= R) {
    tag[x] += w;
    if(mn[x]) sum[x] -= num[x];
    mn[x] += w;
    if(mn[x]) sum[x] += num[x];
    return ;
  }
  down(x);
  int mid = (l + r) >> 1;
  if(L <= mid) upd(ls, l, mid, L, R, w);
  if(R > mid) upd(rs, mid + 1, r, L, R, w);
  up(x);
  // printf("x = %d mn = %d num = %d sum = %d\n", x, mn[x], num[x], sum[x]);
}

int res = 0, d[N];

void predfs(int u, int fa) {
  st[u] = ++res;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    predfs(to, u);
  }
  ed[u] = res;
}

void dfs(int u, int fa) {
  if(g[u].size()) upd(1, 1, n, st[u], ed[u], 1);
  for(int i = 0; i < g[u].size(); ++i) {
    int now = g[u][i];
    upd(1, 1, n, st[now], ed[now], 1);
  }
  d[u] = sum[1] - (sum[1] > 0);
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    dfs(to, u);
  }
  if(g[u].size()) upd(1, 1, n, st[u], ed[u], -1);
  for(int i = 0; i < g[u].size(); ++i) {
    int now = g[u][i];
    upd(1, 1, n, st[now], ed[now], -1);
  }
}

int main() {
  int m;
  scanf("%d%d", &n, &m);
  for(int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  predfs(1, 0);
  for(int i = 1, x, y; i <= m; ++i) {
    scanf("%d%d", &x, &y);
    g[x].push_back(y);
    g[y].push_back(x);
  }
  build(1, 1, n), dfs(1, 0);
  for(int i = 1; i <= n; ++i)
    printf("%d ", d[i]);
  puts("");
  return 0;
}