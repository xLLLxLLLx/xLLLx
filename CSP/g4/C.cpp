#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10, opt = 3e5;
ll ans = 0;
int a[N], mx[N], mn[N], b[N << 1];

void work(int l, int r) {
  if(l == r) {
    ans++;
    return ;
  }
  int mid = (l + r) >> 1;
  work(l, mid), work(mid + 1, r);
  mn[mid] = mx[mid] = a[mid];
  mn[mid + 1] = mx[mid + 1] = a[mid + 1];
  for(int i = mid - 1; i >= l; --i) {
    mx[i] = max(mx[i + 1], a[i]);
    mn[i] = min(mn[i + 1], a[i]);
  }
  for(int i = mid + 2; i <= r; ++i) {
    mx[i] = max(mx[i - 1], a[i]);
    mn[i] = min(mn[i - 1], a[i]);
  }
  int now = mid + 1;
  for(int i = mid; i >= l; --i) {
    int pos = i + mx[i] - mn[i];
    if(pos >= mid + 1 && pos <= r && mx[pos] < mx[i] && mn[pos] > mn[i]) {
      ans++;
    }
  }
  now = mid;
  for(int i = mid + 1; i <= r; ++i) {
    int pos = i - (mx[i] - mn[i]);
    if(pos >= l && pos <= mid && mx[pos] < mx[i] && mn[i] < mn[pos]) {
      ans++;
    }
  }
  // mn -> left, mx -> right
  // mx[z] - mn[i] = z - i
  // mx[z] - z = mn[i] - i;
  int L = mid + 1, R = mid + 1;
  for(int i = mid; i >= l; --i) {
    while(R <= r && mn[R] > mn[i]) {
      int pos = mx[R] - R + opt;
      b[pos]++;
      R++;
    }
    while(L < R && mx[L] < mx[i]) {
      int pos = mx[L] - L + opt;
      b[pos]--;
      L++;
    }
    int pos = mn[i] - i + opt;
    ans += b[pos];
  }
  while(L < R) b[mx[L] - L + opt]--, L++;
  L = R = mid;
  // mx -> left mn -> right
  // mx[z] - mn[i] = i - z
  // mx[z] + z = mn[i] + i
  for(int i = mid + 1; i <= r; ++i) {
    while(L >= l && mn[L] > mn[i]) {
      int pos = mx[L] + L;
      b[pos]++;
      L--;
    }
    while(L < R && mx[R] < mx[i]) {
      int pos = mx[R] + R;
      b[pos]--;
      R--;
    }
    int pos = mn[i] + i;
    ans += b[pos];
  }
  while(L < R) b[mx[R] + R]--, R--;
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1, x, y; i <= n; ++i) {
    scanf("%d%d", &x, &y);
    a[x] = y;
  }
  work(1, n);
  printf("%lld\n", ans);
  return 0;
}