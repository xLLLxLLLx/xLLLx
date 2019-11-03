#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N];

int main() {
  int T;
  cin >> T;
  for(int o = 1; o <= T; ++o) {
    int n;
    cin >> n;
    int ans = 0, pos = 0;
    for(int i = 1, x; i <= n; ++i) {
      scanf("%1d", &x);
      if(x) ans = max(ans, max(i, n - i + 1));
    }
    printf("%d\n", max(n, ans * 2));
  }
  return 0;
}