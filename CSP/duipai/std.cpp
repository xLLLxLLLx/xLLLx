#include <bits/stdc++.h>
using namespace std;
const int N = 5e5 + 10;
int f[N], g[N];

int find(int k) {
  return f[k] == k ? f[k] : f[k] = find(f[k]);
}

int main() {
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; ++i) f[i] = i;
  for(int o = 1; o <= m; ++o) {
    int tp, x, y;
    cin >> tp >> x >> y;
    if(tp == 1) {
      int fx = find(x), fy = find(y);
      f[fx] = fy;
    } else {
      for(int i = 1; i <= n; ++i) {
        if(find(i) == find(x)) g[i] += y;
      }
    }
  }
  for(int i = 1; i <= n; ++i)
    printf("%d ", g[i]);
  puts("");
  return 0;
}