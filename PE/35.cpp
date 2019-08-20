#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 1e7 + 1, M = 3e6 + 1;
int pr[M];
bool flg[N];

void init() {
  flg[1] = 1;
  for(int i = 2; i < N; ++i) {
    if(!flg[i]) pr[++pr[0]] = i;
    for(int j = 1; j <= pr[0]; ++j) {
      if(i * pr[j] >= N) break;
      flg[i * pr[j]] = 1;
      if(i % pr[j] == 0) break;
    }
  }
}

int nm[10];
bool check(int x) {
  nm[0] = 0;
  for(; x; x /= 10) nm[++nm[0]] = x % 10;
  reverse(nm + 1, nm + 1 + nm[0]);
  for(int i = 1; i <= nm[0]; ++i) {
    int pos = 0;
    for(int j = 1; j <= nm[0]; ++j) {
      int x = (i + j - 1);
      while(x > nm[0]) x -= nm[0];
      pos = pos * 10 + nm[x];
    }
    // printf("%d\n", pos);
    if(flg[pos]) return false;
  }
  return true;
}

int main() {
  init();
  int ans = 0;
  check(197);
  for(int i = 2; i < 1000000; ++i) {
    if(check(i)) {
      // printf("%d\n", i);
      ans ++;
    }
  }
  // check(89759);
  printf("%d\n", ans);
  return 0;
}