#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 28123;
int flg[N + 10];

int main() {
  for(int i = 1; i <= N; ++i) {
    int len = sqrt(i), pos = 0;
    for(int j = 1; j <= len; ++j) {
      if(i % j == 0) {
        pos += j;
        if(j == 1) continue;
        if(j * j != i)
          pos += i / j;
      }
    }
    if(pos > i) flg[i] = 1;
  }
  ll ans = 0;
  for(int i = 1; i <= N; ++i) {
    int pos = i / 2, gg = 0;
    for(int j = 1; j <= pos; ++j) {
      if(flg[j] && flg[i - j]) {
        gg = 1;
        break;
      }
    }
    if(!gg) ans += i;
  }
  printf("%lld\n", ans);
  return 0;
}