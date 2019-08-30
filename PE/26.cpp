#include <bits/stdc++.h>
using namespace std;
const int N = 1e4 + 10;
int nm[N], ans = 0, now = 0;

void dfs(int x, int dep) {
  if(!now) {
    if(dep >= 982) {
      printf("XXXX%d\n", x);
    }
    return ;
  }
  if(nm[now % x]) {
    ans = max(ans, dep - nm[now % x]);
    if(dep - nm[now % x] == 982) printf("x%d\n", x);
    return ;
  }
  nm[now % x] = dep;
  now %= x;
  if(x == 983) printf("%d\n", now);
  now *= 10;
  dfs(x, dep + 1);
}

int main() {
  for(int i = 10; i <= 1000; ++i) {
    memset(nm, 0, sizeof nm);
    now = 10;
    dfs(i, 1);
  }
  printf("ans%d\n", ans);
  return 0;
}