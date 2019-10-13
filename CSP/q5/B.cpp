#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N], b[N];
typedef pair<int, int> P;
map<int, int> ma, mb;
map<P, int> ab;

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1, x, y, z; i <= n; ++i) {
    scanf("%d%d%d", &x, &y, &z);
    a[i] = x + y;
    b[i] = x - z;
  }
  int ans = 0, cnt = 0, la = 0, lb = 0;
  for(int i = 1, j = 1; i <= n; ++i) {
    ma[a[i]]++, mb[b[i]]++, ab[P(a[i], b[i])]++;
    if(i > 1 && a[i] != a[i - 1]) {
      la = i - 1;
    }
    if(i > 1 && b[i] != b[i - 1]) {
      lb = i - 1;
    }
    for(;;) {
      if(la < j || lb < j) break;
      int pos = ma[a[i]] + mb[b[la]] - ab[P(a[i], b[la])];
      if(pos == i - j + 1) {
        break;
      }
      pos = ma[a[lb]] + mb[b[i]] - ab[P(a[lb], b[i])];
      if(pos == i - j + 1) {
        break;
      }
      ma[a[j]]--, mb[b[j]]--, ab[P(a[j], b[j])]--;
      j++;
    }
    int len = i - j + 1;
    // printf("%d %d %d\n", i, j, len);
    if(len > ans) {
      ans = len;
      cnt = 1;
    } else if(ans == len) {
      cnt++;
    }
  }
  printf("%d %d\n", ans, cnt);
  return 0;
}