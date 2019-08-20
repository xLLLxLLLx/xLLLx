#include <bits/stdc++.h>
#define ll long long
using namespace std;

int js(int x) {
  return x * x * x * x * x;
}

int nm[10];
bool check(int x) {
  nm[0] = 0;
  int y = x;
  for(; x; x /= 10) nm[++nm[0]] = x % 10;
  ll pos = 0;
  for(int i = 1; i <= nm[0]; ++i) {
    pos += js(nm[i]);
  }
  return pos == y;
}

int main() {
  ll ans = 0;
  for(int i = 2; i < 10000000; ++i) {
    if(check(i)) {
      ans += i;
    }
  }
  printf("%d\n", ans);
  return 0;
}