#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 15;
ll ans = 0;
int a[N], mk[N], pr[N];

void check() {
  for(int i = 2; i <= 8; ++i) {
    int pos = 0;
    for(int j = 0; j < 3; ++j) {
      pos = pos * 10 + a[i + j];
    }
    if(pos % pr[i - 1]) return ;
  }
  ll tmp = 0;
  for(int i = 1; i <= 10; ++i) 
    tmp = tmp * 10 + a[i];
  ans += tmp;
}

void dfs(int dep) {
  if(dep > 10) {
    check();
    return;
  }
  for(int i = 0; i <= 9; ++i) {
    if(!mk[i]) {
      a[dep] = i;
      mk[i] = 1;
      dfs(dep + 1);
      mk[i] = 0;
    }
  }
}

int main() {
  for(int i = 1; i <= 7; ++i) cin >> pr[i];
  dfs(1);
  printf("%lld\n", ans);
  return 0;
}