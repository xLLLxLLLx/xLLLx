#include <bits/stdc++.h>
using namespace std;
int nm[15];
int maxn = 0;

int main() {
  for(int i = 1; i <= 10000; ++i) {
    memset(nm, 0, sizeof nm);
    int pos = 0, flg = 1, res = 0;
    for(int j = 1; ; ++j) {
      int tmp = i * j, zs = 0;
      for(; tmp; tmp /= 10) {
        int gg = tmp % 10;
        pos *= 10;
        if(nm[gg] || !gg) {
          flg = 0;
          break;
        } else {
          nm[gg] = 1;
          res++;
        }
      }
      if(!flg) break;
      pos += i * j;
      if(res == 9) break;
    }
    if(flg) maxn = max(maxn, pos);
  }
  printf("%d\n", maxn);
  return 0;
}