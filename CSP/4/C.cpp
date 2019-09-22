#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10, mod = 1e9 + 7;
struct data {
  int nt, to, w;
} a[N << 1];
map<int, int> mp[N];
typedef pair<int, int> P;
ll jc[N];
P l[N];
int head[N], vis[N], f[N], h[N], d[N], c[N], L = 0, flg = 0, cnt = 0;

void add(int x, int y, int w) {
  a[++cnt].to = y;
  a[cnt].w = w;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void adde(int x, int y, int w) {
  d[x]++, d[y]++;
  add(x, y, w), add(y, x, w);
}

void dfs(int u, int fa) {
  if(flg) return ;
  c[++c[0]] = u;
  vis[u] = 1, f[u] = fa;
  for(int i = head[u]; i; i = a[i].nt) {
    int to = a[i].to;
    if(to == fa || flg) continue;
    if(vis[to]) {
      flg = 1;
      int res = 0;
      int uu = u;
      for(; uu != to; uu = f[uu]) ++res;
      h[++h[0]] = res + 1;
      return ;
    } else dfs(to, u);
  }
}

ll mul(ll x, ll y) {
  return x * y % mod;
}

void init() {
  jc[0] = 1;
  for(int i = 1; i < N; ++i)
    jc[i] = mul(jc[i - 1], i);
}

ll q_pow(int x, int y) {
  ll ans = 1;
  for(; y; y >>= 1) {
    if(y & 1)
      ans = mul(ans, x);
    x = mul(x, x);
  }
  return ans;
}

int main() {
  init();
  int T;
  scanf("%d", &T);
  int n, one, two, lop = 0;
  scanf("%d%d%d", &n, &one, &two);
  ll ans = 1;
  for(int i = 1, x, y; i <= one; ++i) {
    scanf("%d%d", &x, &y);
    if(mp[x][y]) {
      lop++;
      vis[x] = vis[y] = 1;
    } 
    mp[x][y] = mp[y][x] = 1;
    adde(x, y, 0);
  }
  for(int i = 1, x, y; i <= two; ++i) {
    scanf("%d%d", &x, &y);
    if(mp[x][y]) {
      lop++;
      vis[x] = vis[y] = 1;
    }
    mp[x][y] = mp[y][x] = 1;
    adde(x, y, 1);
  }
  //printf("%d\n", lop);
  ans = mul(ans, mul(q_pow(2, lop), jc[lop]));
  for(int i = 1; i <= n; ++i) {
    if(d[i] <= 1 && !vis[i]) {
      flg = c[0] = 0, dfs(i, 0);
      l[++L] = P(c[0], a[head[i]].w);
    }
  }
  for(int i = 1; i <= n; ++i) {
    if(!vis[i]) {
      flg = c[0] = 0, dfs(i, 0);
    }
  }
 // printf("%d %d\n", L, h[0]);
  sort(h + 1, h + 1 + h[0]);
  for(int i = 1; i <= h[0]; ++i) {
    int k = i;
    for(int j = i; j <= h[0]; ++j) {
      if(h[i] == h[j]) {
        k = j;
      }
    }
    int num = k - i + 1;
    //printf("%d\n", h[i]);
    ll pos = mul(q_pow(h[i], num), jc[num]);
    ans = mul(ans, pos);
    i = k;
  }
  sort(l + 1, l + 1 + L);
  for(int i = 1; i <= L; ++i) {
    int k = i;
    if(l[i].first & 1) {
      for(int j = i; j <= L; ++j) {
        if(l[i].first == l[j].first) {
          k = j;
        }
      }
    } else {
      for(int j = i; j <= L; ++j) {
        if(l[i] == l[j]) {
          k = j;
        }
      }
    }
    int num = k - i + 1;
    //printf("%d\n", l[i].first);
    int pos = 2 - (l[i].first & 1);
    ans = mul(ans, (mul(q_pow(pos, num), jc[num])));
    i = k;
  }
  //printf("%lld\n", ans);
  //printf("%lld\n", jc[n]);
  printf("%lld\n", (jc[n] - ans + mod) % mod);
  return 0;
}