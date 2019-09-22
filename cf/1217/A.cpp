#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  int T;
  cin >> T;
  for(int o = 1; o <= T; ++o) {
    int x, y, z;
    cin >> x >> y >> z;
    int pos = x - y - z;
    pos = -pos;
    if(pos < 0) printf("%d\n", z + 1);
    else {
      int gg = pos / 2 + 1;
      gg = z - gg + 1;
      printf("%d\n", max(0, gg));
    }
  }
  return 0;
}