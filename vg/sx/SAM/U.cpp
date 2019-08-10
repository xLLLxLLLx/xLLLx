#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e6 + 10, mod = 1e9 + 7;
struct node {
  int fa, mx, ch[12];
} a[N << 1];
int cnt, last;

void init() {
  cnt = last = 1;
  memset(a, 0, sizeof a);
}

void insert(int x) {
  int p = last, np = ++cnt;
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

ll mul(ll x, ll y) {
  return x * y % mod;
}

ll add(ll x, ll y) {
  return (x + y) % mod;
}

int d[N << 1];
ll sz[N << 1], dp[N << 1];

queue<int> q;

void solve() {
  q.push(1);
  while(!q.empty()) {
  	int h = q.front(); q.pop();
  	for(int i = 0; i < 10; ++i) {
  		if(a[h].ch[i]) {
  			if(!d[a[h].ch[i]])
  				q.push(a[h].ch[i]);
  			d[a[h].ch[i]]++;
  		}
  	}
  }
  q.push(1);
  sz[1] = 1;
  while(!q.empty()) {
  	int h = q.front(); q.pop();
  	for(int i = 0; i < 10; ++i) {
  		int pos = a[h].ch[i];
  		if(pos) {
  			sz[pos] += sz[h];
  			dp[pos] = add(dp[pos], add(mul(dp[h], 10), mul(sz[h], i)));
  			d[pos]--;
  			if(!d[pos]) {
  				q.push(pos);
  			}
  		}
  	}
  }
  ll ans = 0;
  for(int i = 1; i <= cnt; ++i)
    ans = add(ans, dp[i]);
  printf("%lld\n", ans);
}

char lx[N];

int main() {
  init();
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    scanf("%s", lx + 1);
    int len = strlen(lx + 1);
    for(int i = 1; i <= len; ++i)
      insert(lx[i] - '0');
    insert(10);
  }
  solve();
  return 0;
}
