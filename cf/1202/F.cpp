#include <bits/stdc++.h>
using namespace std;

int main() {
  int a, b;
  cin >> a >> b;
  int n = a + b;
  int ans = 0;
  for(int sz = 1; sz <= n; ) {
    int A = n / sz;
    int B = n / A;
    if(a >= A && b >= A) {
      int l1 = (a + A) / (A + 1);
      int r1 = a / A;
      int l2 = (b + A) / (A + 1);
      int r2 = b / A;
      if(l1 <= r1 && l2 <= r2) {
        ans += max(0, min(B, r1 + r2) - max(sz, l1 + l2) + 1);
      } 
    }
    sz = B + 1;
  }
  printf("%d\n", ans);
  return 0;
}
