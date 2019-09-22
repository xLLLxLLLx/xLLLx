#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 110;
struct data {
  int x, y;
} a[N];

bool cmp(data A, data B) {
  return A.x - A.y > B.x - B.y;
}

int main() {
  int T;
  cin >> T;
  for(int o = 1; o <= T; ++o) {
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
      scanf("%d%d", &a[i].x, &a[i].y);
    }
    sort(a + 1, a + 1 + n, cmp);
    // for(int i = 1; i <= n; ++i) {
    //   printf("%d %d\n", a[i].x, a[i].y);
    // }
    int ans = 1e9;
    for(int i = 1; i <= n; ++i) {
      int pos = m - (a[i].x);
      if(pos <= 0) ans = 1;
      else {
        for(int j = 1; j <= n; ++j) {
          if(a[j].x <= a[j].y) continue;
          int zz = pos / (a[j].x - a[j].y);
          if(pos % (a[j].x - a[j].y)) zz++;
          ans = min(ans, zz + 1);
        }
      }
    }
    if(ans == 1e9) puts("-1");
    else printf("%d\n", ans);
  }
  return 0;
}