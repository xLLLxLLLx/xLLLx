#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 3e5 + 10, mod = 998244353;
struct data {
  int x, y;
} a[N];
int nx[N], ny[N];
ll jc[N];

bool cmp(data A, data B) {
  if(A.x == B.x) return A.y < B.y;
  return A.x < B.x;
}

void init() {
  jc[0] = 1;
  for(int i = 1; i < N; ++i)
    jc[i] = jc[i - 1] * i % mod;
}

int main() {
  init();
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%d%d", &a[i].x, &a[i].y);
    nx[a[i].x]++, ny[a[i].y]++;
  }
  sort(a + 1, a + 1 + n, cmp);
  ll tot = jc[n], pos = 1;
  for(int i = 1; i <= n; ++i) {
    if(a[i].y < a[i - 1].y) {
      pos = 0;
      break;
    }
    int j = i;
    for(; j + 1 <= n && a[j + 1].x == a[j].x; ++j);
    // printf("%d %d\n", i, j);
    for(int k = i; k <= j; ++k) {
      int t = k;
      for(; t + 1 <= j && a[t + 1].y == a[t].y; ++t);
      pos = pos * jc[t - k + 1] % mod;
      k = t;
    }
    i = j;
  }
  // printf("%lld\n", pos);
  tot = (tot + pos) % mod;
  ll numx = 1, numy = 1;
  for(int i = 1; i <= n; ++i) {
    numx = numx * jc[nx[i]] % mod;
    numy = numy * jc[ny[i]] % mod;
  }
  tot = (tot - numx + mod) % mod;
  tot = (tot - numy + mod) % mod;
  printf("%lld\n", tot);
  return 0;
}