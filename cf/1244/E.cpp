#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e5 + 10;
int n;
ll a[N], qz[N], k;

ll check(int l) {
  return (qz[n] - qz[l - 1]) - a[l] * (n - l + 1);
}

int get(int l, ll yu) {
  int L = l, R = n, ans = n;
  while(L <= R) {
    int mid = (L + R) >> 1;
    if(check(mid) <= yu) ans = mid, R = mid - 1;
    else L = mid + 1;
  }
  return ans;
}

int main() {
  cin >> n >> k;
  for(int i = 1; i <= n; ++i) {
    scanf("%lld", &a[i]);
  }
  sort(a + 1, a + 1 + n);
  ll ans = a[n] - a[1];
  for(int i = 1; i <= n; ++i) {
    qz[i] = qz[i - 1] + a[i];
  }
  for(int i = 1; i <= n; ++i) {
    ll pos = a[i] * i - qz[i];
    if(pos > k) break;
    if(i == n) {
      ans = 0;
      break;
    }
    int tmp = get(i + 1, k - pos);
    // printf("%d %d\n", i, tmp);
    ll now = a[tmp] - a[i];
    ll yu = k - pos - check(tmp);
    if(i > n - tmp + 1) {
      ll gg = min(a[tmp] - a[tmp - 1], yu / (n - tmp + 1));
      yu -= gg * (n - tmp + 1);
      now -= gg;
      now -= min(a[i + 1] - a[i], yu / i);
    } else {
      ll gg = min(a[i + 1] - a[i], yu / i);
      yu -= gg * i;
      now -= gg;
      now -= min(a[tmp] - a[tmp - 1], yu / (n - tmp + 1));
    }
    // printf("%lld\n", now);
    ans = min(ans, max(0ll, now));
  }
  printf("%lld\n", ans);
  return 0;
}