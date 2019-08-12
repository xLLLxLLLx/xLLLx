#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e6 + 10;
int size = 0;
int son[N * 20][2], sz[N * 20];

#define ls son[x][0]
#define rs son[x][1]

void AddNode(int &x, int l, int r, int L) {
  x = ++size;
  if(l == r) {
    sz[x]++;
    return ;
  }
  int mid = (l + r) >> 1;
  if(L <= mid) AddNode(ls, l, mid, L);
  else AddNode(rs, mid + 1, r, L);
  sz[x] = sz[ls] + sz[rs];
}

int merge(int a, int b, int l, int r) {
  if(!a || !b) return a + b;
  int x = ++size;
  if(l == r) {
    sz[x] = sz[a] + sz[b];
    return x;
  }
  int mid = (l + r) >> 1;
  ls = merge(son[a][0], son[b][0], l, mid);
  rs = merge(son[a][1], son[b][1], mid + 1, r);
  sz[x] = sz[ls] + sz[rs];
  return x;
}

int Ask(int x, int l, int r, int L, int R) {
  if(L <= l && r <= R)
    return sz[x];
  int mid = (l + r) >> 1, ans = 0;
  if(L <= mid) ans += Ask(ls, l, mid, L, R);
  if(R > mid) ans += Ask(rs, mid + 1, r, L, R);
  return ans;
}

vector<int> g[N << 1];
int rt[N << 1], lim[N << 1];

namespace SAM1 {//2017
  int last = 1, cnt = 1, n;
  
  struct node {
    int fa, mx, ch[26];
  } a[N << 1];
 
  void insert(int id, int x) {
    int p = last, np = ++cnt;
    AddNode(rt[np], 1, n, id);
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
  
  void add() {
    for(int i = 2; i <= cnt; ++i)
      g[a[i].fa].push_back(i);
  }

  void dfs(int x) {
    for(int i = 0; i < g[x].size(); ++i) {
      dfs(g[x][i]);
      rt[x] = merge(rt[x], rt[g[x][i]], 1, n);
    }   
  }

  void solve(char *s, int L, int R) {
    int len = strlen(s);
    int u = 1, l = 0;
    for(int i = 0; i < len; ++i) {
      int x = s[i] - 'a'; 
      for(; u && !a[u].ch[x]; u = a[u].fa, l = a[u].mx);
      if(!a[u].ch[x]) {
        u = 1, l = 0;
        continue;
      }
      u = a[u].ch[x], l++;
      for(; u > 1; ) {
        if(Ask(rt[u], 1, n, L + l - 1, R)) break;
        if(--l == a[a[u].fa].mx) u = a[u].fa;
      }
      if(u == 1) continue;
      for(int j = 0; j < g[i].size(); ++j) {
        lim[g[i][j]] = max(lim[g[i][j]], l);
      }
    }
  }
}

namespace SAM2 {//2018
  int last = 1, cnt = 1;
  struct node {
    int fa, mx, ch[26];
    void clear() {
      fa = mx = 0;
      memset(ch, 0, sizeof ch);
    }
  } a[N << 1];

  void clear(int n) {
    last = cnt = 1;
    for(int i = 1; i <= n; ++i)
      a[i].clear(), g[i].clear();
    fill(lim + 1, lim + 1 + n, 0);
  }

  void insert(int id, int x) {
    int p = last, np = ++cnt;
    g[id].push_back(np);
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
        g[id].push_back(nq);
        a[nq] = a[q];
        a[nq].mx = a[p].mx + 1;
        a[q].fa = a[np].fa = nq;
        for(; p && a[p].ch[x] == q; p = a[p].fa) 
          a[p].ch[x] = nq;
      }
    }
    last = np;
  }

  ll solve() {
    ll ans1 = 0, ans2 = 0;
    for(int i = 1; i <= cnt; ++i) {
      ans1 += a[i].mx - a[a[i].fa].mx;
      ans2 += max(0, min(lim[i], a[i].mx) - a[a[i].fa].mx);
    }
    return ans1 - ans2;
  }
};

char lx[N];

int main() {
  freopen("name.in", "r", stdin);
  freopen("name.out", "w", stdout);
  scanf("%s", lx + 1); 
  int len = strlen(lx + 1);
  SAM1::n = len;
  for(int i = 1; i <= len; ++i)
    SAM1::insert(i, lx[i] - 'a');
  SAM1::add(), SAM1::dfs(1);
  int T;
  scanf("%d", &T);
  for(int o = 1, l, r; o <= T; ++o) {
    scanf("%s%d%d", lx, &l, &r);
    SAM2::clear(strlen(lx) * 2);
    int n = strlen(lx);
    for(int i = 0; i < n; ++i)
      SAM2::insert(i, lx[i] - 'a');
    SAM1::solve(lx, l, r);
    printf("%lld\n", SAM2::solve());
  }
  return 0;
}