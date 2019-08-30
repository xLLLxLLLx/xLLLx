#include <bits/stdc++.h>
using namespace std;

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int b, p, f, h, c;
    cin >> b >> p >> f;
    cin >> h >> c;
    int ans = 0;
    if(h >= c) {
      int pos = min(p, b / 2);
      ans += pos * h;
      b -= 2 * pos;
      pos = min(f, b / 2);
      ans += pos * c;
    } else {
      int pos = min(f, b / 2);
      ans += pos * c;
      b -= 2 * pos;
      pos = min(p, b / 2);
      ans += pos * h;
    }
    printf("%d\n", ans);
  }
  return 0;
}