#include <bits/stdc++.h>
#define ll long long
using namespace std;
int jc[11];

bool check(int x) {
  int y = x, pos = 0;
  for(; x; x /= 10) pos += jc[x % 10];
  return pos == y;
}

int main() {
  jc[0] = 1;
  for(int i = 1; i <= 10; ++i) jc[i] = jc[i - 1] * i;
  ll ans = 0;
  for(int i = 10; i <= 10000000; ++i) {
    if(check(i))
      ans += i;
  }
  printf("%lld\n", ans);
  return 0;
}