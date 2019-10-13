#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, LOG = 21;
struct data {
  int nt, to;
} a[N << 1];
int all = 0;
set<int> st;
set<int> :: iterator sit, nt, bf;
int n, k, ans = 0, res = 0, cnt = 0;
int dep[N], dfn[N], ys[N], head[N], g[N][LOG + 1];

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void get() {
  for(int j = 1; j <= LOG; ++j)
    for(int i = 1; i <= n; ++i)
      g[i][j] = g[g[i][j - 1]][j - 1];
}

void dfs(int u, int fa) {
  dfn[u] = ++res, ys[res] = u;
  dep[u] = dep[fa] + 1, g[u][0] = fa;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa) continue;
    dfs(to, u);
  }
}

int GetLCA(int A, int B) {
  if(dep[A] > dep[B]) swap(A, B);
  for(int i = LOG; i >= 0; --i)
    if(dep[g[B][i]] >= dep[A]) B = g[B][i];
  if(A == B) return A;
  for(int i = LOG; i >= 0; --i)
    if(g[A][i] != g[B][i])
      A = g[A][i], B = g[B][i];
  return g[A][0];
}

int getdis(int x, int y) {
  x = ys[x], y = ys[y];
  return dep[x] + dep[y] - 2 * dep[GetLCA(x, y)];
}

void Add(int x, int flg) {
  if(flg > 0 && !st.size()) {
    st.insert(x);
    return ;
  }
  all -= getdis(*st.begin(), *(--st.end()));
  if(flg > 0) {
    st.insert(dfn[x]);
  }
  sit = st.lower_bound(dfn[x]);
  int be = 0, ed = 0;
  if(sit != st.begin()) {
    be = 1;
    bf = sit;
    bf--;
    all += flg * getdis(*sit, *bf);
  }
  if(sit != (--st.end())) {
    ed = 1;
    nt = sit;
    nt++;
    all += flg * getdis(*sit, *nt);
  }
  if(be && ed) {
    all += (-flg) * getdis(*bf, *nt);
  }
  if(flg < 0) {
    st.erase(dfn[x]);
  }
  if(st.size()) {
    all += getdis(*st.begin(), *st.rbegin());
  }
}

int main() {
  scanf("%d%d", &n, &k);
  for(int i = 1, x, y; i < n; ++i) {
    scanf("%d%d", &x, &y);
    add(x, y), add(y, x);
  }
  dfs(1, 0), get();
  for(int l = 1, r = 1; l <= n; ++l) {
    while(r <= n && all / 2 + 1 <= k) {
      // printf("qwq%d %d\n", l, r);
      ans = max(ans, r - l), Add(r++, 1);
    }
    if(r > n) break;
    Add(l, -1);
  }
  if(n == 1) printf("1\n");
  else printf("%d\n", ans);
  return 0;
}