#include <bits/stdc++.h>
using namespace std;
const int N = 10;
int a[N], nm[N], res = 0;

void dfs(int dep) {
  if(dep == 10) {
    res++;
    if(res == 1000000) {
      for(int i = 0; i < 10; ++i) {
        printf("%d", a[i]);
      }
      puts("");
      exit(0);
    }
    return ;
  }
  for(int i = 0; i < 10; ++i) {
    if(!nm[i]) {
      nm[i] = 1;
      a[dep] = i;
      dfs(dep + 1);
      nm[i] = 0;
    }
  }
}

int main() {
  dfs(0);
  return 0;
}