#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1, x; o <= T; ++o) {
    scanf("%d", &x);
    if(x <= 100) {
      ll ans = 1;
      for(int i = 1; i < x; ++i)
        ans = ans * i % x;
      printf("%lld\n", ans);
    } else {
      int len = sqrt(x), flg = 1;
      for(int i = 2; i <= len; ++i) {
        if(x % i == 0) flg = 0;
      }
      if(flg) printf("%d\n", x - 1);
      else printf("0\n");
    }
  }
  return 0;
}
/*4*/