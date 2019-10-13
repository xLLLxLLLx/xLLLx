#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10;
int a[N];
ll qz[N];

void add(int l, int r, int k) {
  if(l > r) return ;
  // printf("%d %d %d\n", l, r, k);
  qz[l] += k, qz[r + 1] -= k;
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= m; ++i) {
    scanf("%d", &a[i]);
    if(i > 1) {
      int pos = max(a[i], a[i - 1]), tmp = min(a[i], a[i - 1]);
      if(pos == tmp) continue;
      add(1, tmp - 1, pos - tmp);
      add(tmp, tmp, pos - 1);
      add(tmp + 1, pos - 1, pos - tmp - 1);
      add(pos, pos, tmp);
      add(pos + 1, n, pos - tmp);
    }
  }
  for(int i = 1; i <= n; ++i) qz[i] += qz[i - 1];
  for(int i = 1; i <= n; ++i) {
    printf("%lld ", qz[i]);
  }
  puts("");
  return 0;
}