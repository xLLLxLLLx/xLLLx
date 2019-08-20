#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N], n, m;
 
int find2(int x) {
  for(int i = x + 1; i <= n; ++i) {
    if(a[i] == 2) return i;
  }
  return 0;
}
 
int find0(int x) {
  for(int i = x; i >= 0; --i) {
    if(!a[x]) return i;
  }
  return 0;
}
 
int main() {
  freopen("counter.in", "r", stdin);
  freopen("counter.out", "w", stdout);
  scanf("%d%d", &n, &m);
  for(int i = 1, x; i <= m; ++i) {
    scanf("%d", &x);
    if(a[x] == 2) {
      a[x + 1]++, a[x] = 1;
      printf("2 %d %d %d %d\n", x, a[x], x + 1, a[x + 1]);
    } else if(!a[x]) {
      int pos = find2(x);
      if(!pos) {
        a[x] = 1;
        printf("1 %d %d\n", x, a[x]);
      } else {
        a[pos] = 0, a[pos + 1]++, a[x]++;
        printf("3 %d %d %d %d %d %d\n", x, a[x], pos, a[pos], pos + 1, a[pos + 1]);
      }
    } else {
      int pos = find2(x);
      if(!pos) {
        a[x] = 0, a[x + 1]++;
        printf("2 %d %d %d %d\n", x, a[x], x + 1, a[x + 1]);
      } else if(pos == x + 1) {
        a[x] = 2, a[pos] = 0, a[pos + 1]++;
        printf("3 %d %d %d %d %d %d\n", x, a[x], pos, a[pos], pos + 1, a[pos + 1]);
      } else {
        a[x] = 0, a[x + 1]++, a[pos] = 0, a[pos + 1]++;
        printf("4 %d %d %d %d %d %d %d %d\n", x, a[x], x + 1, a[x + 1], pos, a[pos], pos + 1, a[pos + 1]);
      }
    }
  }
  return 0;
}