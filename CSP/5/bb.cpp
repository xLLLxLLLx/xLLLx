#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10, M = 1e6 + 10;
int n, k;
ll ans = 0;
int a[N], qz[N], b[M];

void work(int l, int r) {
  if(l == r) return ;
  int mid = (l + r) >> 1;
  work(l, mid), work(mid + 1, r);
  // printf("l = %d, r = %d\n", l, r);
  int now = mid + 1, mx = 0;
  // printf("L = %d MID = %d\n", l, mid);
  for(int i = mid; i >= l; --i) {
    mx = max(mx, a[i]);
    while(a[now] <= mx && now <= r) b[qz[now]]++, now++;
    int pos = (mx + qz[i - 1]) % k;
    // printf("i = %d now = %d mx = %d pos = %d da = %d\n", i, now, mx, pos, b[pos]);
    ans += b[pos];
  }
  for(int i = mid + 1; i < now; ++i) b[qz[i]]--;
  now = mid, mx = 0;
  // printf("MID = %d R = %d\n", mid + 1, r);
  for(int i = mid + 1; i <= r; ++i) {
    mx = max(mx, a[i]);
    while(a[now] < mx && now >= l) b[qz[now - 1]]++, now--;
    int pos = ((qz[i] - mx) % k + k) % k;
    // printf("i = %d now = %d mx = %d pos = %d da = %d\n", i, now, mx, pos, b[pos]);
    ans += b[pos];
  }
  for(int i = now + 1; i <= mid; ++i) b[qz[i - 1]]--;
}

int main() {
  scanf("%d%d", &n, &k);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
    qz[i] = (qz[i - 1] + a[i]) % k;
  }
  work(1, n);
  printf("%lld\n", ans);
  return 0;
}