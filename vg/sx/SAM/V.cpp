#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
struct node {
  int fa, mx, ch[26];
} a[N << 1];
char lx[N];
int vis[N << 1], R[N << 1], w[N << 1], id[N << 1];
int b[N << 1], len, cnt, last;

void init() {
  cnt = last = 1;
  memset(a, 0, sizeof a);
}

void insert(int x) {
  int p = last, np = ++cnt;
  R[np] = 1;
  a[np].mx = a[p].mx + 1;
  for(; p && !a[p].ch[x]; p = a[p].fa)
    a[p].ch[x] = np;
  if(!p) {
    a[np].fa = 1;
  } else {
    int q = a[p].ch[x];
    if(a[q].mx == a[p].mx + 1) {
      a[np].fa = q;
    } else {
      int nq = ++cnt;
      a[nq] = a[q];
      a[nq].mx = a[p].mx + 1;
      a[np].fa = a[q].fa = nq;
      for(; p && a[p].ch[x] == q; p = a[p].fa)
        a[p].ch[x] = nq;
    }
  }
  last = np;
}

void solve() {
  fill(vis + 1, vis + 1 + cnt, 0);
  int n = strlen(lx + 1);
  for(int i = 1; i <= n; ++i)
    b[i] = lx[i] - 'a';
  for(int i = 1; i < n; ++i)
    b[i + n] = b[i];
  int u = 1, l = 0, ans = 0;
  for(int i = 1; i < 2 * n; ++i) {
    for(; u && !a[u].ch[b[i]]; u = a[u].fa, l = a[u].mx) ;
    if(a[u].ch[b[i]]) {
      u = a[u].ch[b[i]], l++;
      if(l >= n) {
        for(; a[u].fa && a[a[u].fa].mx >= n; u = a[u].fa, l = a[u].mx);
        if(!vis[u]) ans += R[u];
        vis[u] = 1;
      }
    }
  } 
  printf("%d\n", ans); 
}

void prepare() {
  for(int i = 1; i <= cnt; ++i)
    w[a[i].mx]++;
  for(int i = 1; i <= len; ++i)
    w[i] += w[i - 1];
  for(int i = 1; i <= cnt; ++i)
    id[w[a[i].mx]--] = i;
  for(int i = cnt; i >= 1; --i)
    R[a[id[i]].fa] += R[id[i]];
}

int main() {
  init();
  scanf("%s", lx + 1);
  len = strlen(lx + 1);
  for(int i = 1; i <= len; ++i) {
    insert(lx[i] - 'a'); 
  }
  prepare();
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    scanf("%s", lx + 1);
    solve();
  }
  return 0;
}
