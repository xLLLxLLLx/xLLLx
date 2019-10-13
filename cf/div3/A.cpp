#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int a[N];

int main() {
  int q;
  cin >> q;
  for(int o = 1; o <= q; ++o) {
    int n, sum = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      sum += a[i];
    }
    int pos = sum / n + (sum % n > 0);
    printf("%d\n", pos);
  }
  return 0;
}