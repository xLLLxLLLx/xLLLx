#include <bits/stdc++.h>
#define ll long long
using namespace std;
int nm[30];

bool check(int x) {
  nm[0] = 0;
  int y = x;
  for(; y; y /= 10) nm[++nm[0]] = y % 10;
  for(int i = 1; i <= nm[0]; ++i)
    if(nm[i] != nm[nm[0] - i + 1]) return false;
  y = x, nm[0] = 0;
  for(; y; y >>= 1) nm[++nm[0]] = y % 2;
  for(int i = 1; i <= nm[0]; ++i)
    if(nm[i] != nm[nm[0] - i + 1]) return false;
  return true;
}

int main() {
  ll ans = 0;
  for(int i = 1; i < 1000000; ++i) {
    if(check(i)) {
      printf("%d\n", i);
      ans += i;
    }
  }
  printf("%lld\n", ans);
  return 0;
}