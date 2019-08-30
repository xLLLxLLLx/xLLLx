#include <bits/stdc++.h>
#define ll long long
using namespace std;

int check(int x) {
  int len = sqrt(x);
  for(int i = 2; i <= len + 2; ++i) {
    if(x % i == 0) return 0;
  }
  return 1;
}

int main() {
  ll ans = 3, now = 7;
  for(int i = 2; i < 50001; ++i) {
    now += 8 * i - 2;
    ans += check(now);
    ans += check(now + i * 2);
    ans += check(now - i * 2);
    ans += check(now - 4 * i);
    int tot = i * 4 + 1;
    if(ans * 10 < tot) {
      printf("%d %d\n", ans, tot);
      printf("%d\n", i * 2 + 1);
      break;
    }
  }
  // printf("%lld\n", ans);
  return 0;
}