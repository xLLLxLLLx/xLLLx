#include <bits/stdc++.h>
#define ll long long
using namespace std;
map<ll, int> mp;
ll ans = 0;
int a[12], b[12];

void check() {
  ll pos = 0;
  for(int i = 1; i <= 5; ++i) {
    pos = pos * 10 + a[i];
    ll tmp = 0;
    for(int j = i + 1; j <= (9 - j) + 1; ++j) {
      tmp = tmp * 10 + a[j];
      ll res = 0;
      for(int k = j + 1; k <= 9; ++k) {
        res = res * 10 + a[k];
      }
      // printf("%lld %lld %lld\n", pos, tmp, res);
      if(pos * tmp == res) {
        if(!mp[res]) ans += res;
        mp[res] = 1;
      }
    }
  }
}

void dfs(int dep) {
  if(dep > 9) {
    check();
    return ;
  }
  for(int i = 1; i <= 9; ++i) {
    if(!b[i]) {
      a[dep] = i;
      b[i] = 1;
      dfs(dep + 1);
      b[i] = 0;
    }
  }
}

int main() {
  dfs(1);
  printf("%lld\n", ans);
  return 0;
}