#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 150010;
struct data {
  int t, s;
} a[N];
int q[N];
ll f[2][N];

int main() {
  int n, m, d;
  scanf("%d%d%d", &n, &m, &d);
  ll ans = 0;
  for(int i = 1, x; i <= m; ++i) {
    scanf("%d%d%d", &a[i].s, &x, &a[i].t);
    ans += x;
  }
  int now = 0;
  a[0].t = 1;
  for(int i = 1; i <= m; ++i) {
    // printf("now = %d\n", i);
    now ^= 1;
    memset(f[now], 0x3f, sizeof f[now]);
    int head = 1, tail = 0, cnt = 1;
    ll dis = 1ll * d * (a[i].t - a[i - 1].t);
    while(cnt <= min(dis, (ll)n)) {
      while(head <= tail && f[now ^ 1][q[tail]] >= f[now ^ 1][cnt]) tail--;
      q[++tail] = cnt;
      cnt++;
    }
    // printf("cnt = %d\n", cnt);
    // for(int j = head; j <= tail; ++j)
      // printf("%d ", q[j]);
    // puts("");
    for(int j = 1; j <= n; ++j) {
      while(head <= tail && j - q[head] > dis) head++;
      if(j + dis <= n) {
        while(head <= tail && f[now ^ 1][q[tail]] >= f[now ^ 1][j + dis]) tail--;
        q[++tail] = j + dis;
        // printf("tail = %d %d\n", tail, j + dis);
      }
      if(head <= tail) {
        // if(q[head] < 0) printf("head = %d %d\n", head, q[head]);
        // printf("j = %d %d %lld\n", j, q[head], f[now ^ 1][q[head]]);
        f[now][j] = f[now ^ 1][q[head]] + abs(a[i].s - j);
        // printf("f[%d][%d] = %lld\n", now, j, f[now][j]);
      }
    }
  }
  // printf("%lld\n", ans);
  ll mn = 1e18;
  for(int i = 1; i <= n; ++i) mn = min(mn, f[now][i]);
  ans -= mn;
  printf("%lld\n", ans);
  return 0;
}