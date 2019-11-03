#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10, M = 5e6 + 10, LOG = 20;
struct data {
  int t, A, B;
} a[M];
int n, m, k;
int st[N][LOG + 1], id[N][LOG + 1], sc[N];
int qz[N], d[N], mx[N], nm[N], pr[N];

void Max(int &x, int y) {
  x = max(x, y);
}

struct node {
  int l, r, w;
  bool operator < (const node &C) const {
    return pr[r] - pr[l - 1] < pr[C.r] - pr[C.l - 1];
  }
};
priority_queue<node> q;

void pre() {
  for(int i = 1; i <= n; ++i) st[i][0] = sc[i], id[i][0] = i;
  for(int j = 1; j <= LOG; ++j) 
    for(int i = 1; i <= n; ++i) {
      if(i + (1 << j) > n + 1) continue;
      if(st[i][j - 1] < st[i + (1 << (j - 1))][j - 1])
        st[i][j] = st[i][j - 1], id[i][j] = id[i][j - 1];
      else 
        st[i][j] = st[i + (1 << (j - 1))][j - 1], id[i][j] = id[i + (1 << (j - 1))][j - 1];
    }
}

typedef pair<int, int> P;
#define fi first
#define se second

P get(int l, int r) {
  int k = (int)(log((double)(r - l + 1)) / log(2.0));
  if(st[l][k] < st[r - (1 << k) + 1][k]) 
    return P(st[l][k], id[l][k]);
  else
    return P(st[r - (1 << k) + 1][k], id[r - (1 << k) + 1][k]);
}

void dfs(int l, int r, int now) {
  if(l > r) return ;
  P pos = get(l, r);
  if(pos.fi > now) {
    q.push((node){l, r, now});
    return ;
  }
  dfs(l, pos.se - 1, now), dfs(pos.se + 1, r, now);
}

int main() {
  scanf("%d%d%d", &n, &m, &k);
  for(int i = 1; i < n; ++i) {
    scanf("%d", &d[i]);
  }
  ll ans = 0;
  for(int i = 1; i <= m; ++i) {
    scanf("%d%d%d", &a[i].t, &a[i].A, &a[i].B);
    ans -= a[i].t;
    nm[a[i].B]++;
    Max(mx[a[i].A], a[i].t); 
  }
  for(int i = 1; i <= n; ++i) {
    pr[i] = pr[i - 1] + nm[i];
    mx[i] = max(mx[i - 1], mx[i]);
  }
  qz[1] = 0;
  for(int i = 2; i <= n; ++i) {
    qz[i] = max(mx[i - 1], qz[i - 1]) + d[i - 1];
  }
  for(int i = 1; i <= n; ++i) {
    ans += 1ll * nm[i] * qz[i];
    sc[i] = max(0, qz[i] - mx[i]);
   printf("sc[%d] = %d\n", i, sc[i]);
  }
  printf("ans = %lld\n", ans);
  pre();
  q.push((node){1, n, 0});
  while(!q.empty()) {
    node h = q.top(); q.pop();
    P pos = get(h.l, h.r);
    if(pos.fi >= k) {
      ans -= 1ll * k * (pr[h.r] - pr[h.l - 1]);
      break;
    }
    ans -= 1ll * pos.fi * (pr[h.r] - pr[h.l - 1]);
    int now = h.w + pos.fi;
    dfs(h.l, pos.se - 1, now), dfs(pos.se + 1, h.r, now);
    k -= pos.fi;
  }
  printf("%lld\n", ans);
  return 0;
}