#include <bits/stdc++.h>
using namespace std;

int main() {
  int ans = 0, be = 0;
  for(int o = 1; o <= 1000; ++o) {
    int res = 0;
    for(int i = o / 3; i <= o; ++i)
      for(int j = 1; j < i; ++j) {
        int k = o - i - j;
        if(k <= 0) continue;
        if(k < i && k < j) {
          if(j * j + k * k == i * i) {
            printf("%d %d %d %d\n", o, i, j, k);
            res++;
          }
        }
      }
    if(res > ans) {
      ans = res;
      be = o;
    }
  }
  printf("%d %d\n", ans, be);
  return 0;
}