#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  cin >> T;
  for(int o = 1; o <= T; ++o) {
    int a, b, c, d, k;
    cin >> a >> b >> c >> d >> k;
    int pos = a / c;
    if(a % c) pos++;
    int tmp = b / d;
    if(b % d) tmp++;
    if(pos + tmp <= k) {
      printf("%d %d\n", pos, tmp);
    } else puts("-1");
  }
  return 0;
}