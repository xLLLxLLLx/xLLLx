#include <bits/stdc++.h>
using namespace std;
const int M = (1 << 14), N = 20;
int n, nm[N], a[M];

void print(int x) {
  nm[0] = 0;
  for( ; x; x >>= 1) nm[++nm[0]] = x % 2;
  while(nm[0] < n) nm[++nm[0]] = 0;
  for(int i = n; i >= 1; --i)
    printf("%d", nm[i]);
  puts("");
}

bool check(int x) {
  int res = 0;
  for(int i = 0; i < 20; ++i) {
    if((x >> i) & 1) res++;
  }
  return res >= n / 2;
}

int main() {
  freopen("code.in", "r", stdin);
  freopen("code.out", "w", stdout);
  scanf("%d", &n);
  // printf("%d\n", n);
  int tot = (1 << n) - 1, gg = 0;
  a[++gg] = 0, a[++gg] = tot;
  for(int i = 1; ; ++i) {
    if(gg + 1 == tot) {
      a[++gg] = i;
      break;
    } else {
      int pos = i ^ a[gg];
      if(check(pos)) {
        a[++gg] = i;
        a[++gg] = tot ^ i;
      } else {
        a[++gg] = tot ^ i;
        a[++gg] = i;
      }
    }
  }
  int be = 1 << (n - 1);
  int ed = 0;
  for(int i = 1; i < gg; ++i) {
    if(check(a[i] ^ be) && check(a[i + 1] ^ be)) {
      ed = i;
    }
  }
  if(!ed) return printf("none\n"), 0;
  for(int i = 1; i <= gg; ++i) {
    print(a[i]);
    if(i == ed) {
      print(be);
    }
  }
  return 0;
}