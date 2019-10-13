#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[2][N];

int main() {
  int t;
  cin >> t;
  for(int o = 1; o <= t; ++o) {
    int n;
    scanf("%d", &n);
    for(int i = 0; i < 2; ++i)
      for(int j = 1; j <= n; ++j) {
        scanf("%1d", &a[i][j]);
        if(a[i][j] <= 2) a[i][j] = 0;
        else a[i][j] = 1;
      }
    int now = 0, flg = 1;
    for(int i = 1; i <= n; ++i) {
      if(!a[now][i]) continue;
      else if(a[now][i] && a[now ^ 1][i]) now ^= 1;
      else {
        puts("NO");
        flg = 0;
        break;
      }
    }
    if(flg && now != 1) puts("NO");
    else if(flg) puts("YES");
  }
  return 0;
}