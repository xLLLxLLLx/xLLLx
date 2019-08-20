#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int ans = 0, mk[N], a[N], mx = 7;

void check() {
  int pos = 0;
  for(int i = 1; i <= mx; ++i)
    pos = pos * 10 + a[i];
  printf("%d\n", pos);
  int len = sqrt(pos);
  for(int i = 2; i <= len; ++i)
    if(pos % i == 0) return ;
  ans = max(ans, pos);
}

void dfs(int dep) {
  if(dep > mx) {
    check();
    return ;
  }
  if(dep == 1) {
    a[1] = 1, mk[1] = 1;
    dfs(dep + 1);
    mk[1] = 0;
    a[1] = 3, mk[3] = 1;
    dfs(dep + 1);
    mk[3] = 0;
    a[1] = 7, mk[7] = 1;
    dfs(dep + 1);
    mk[7] = 0;
    // a[1] = 9, mk[9] = 1;
    // dfs(dep + 1);
  } else {
    for(int i = 1; i <= mx; ++i)
      if(!mk[i]) {
        mk[i] = 1;
        a[dep] = i;
        dfs(dep + 1);
        mk[i] = 0;
      }
  }
}

int main() {
  dfs(1);
  printf("%d\n", ans);
  return 0; 
}