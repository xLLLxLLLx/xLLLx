#include <bits/stdc++.h>
using namespace std;
const int N = 20;
int n, nm[N];

void print(int x) {
  nm[0] = 0;
  for( ; x; x >>= 1) nm[++nm[0]] = x % 2;
  while(nm[0] < n) nm[++nm[0]] = 0;
  for(int i = n; i >= 1; --i)
    printf("%d", nm[i]);
  puts("");
}

int main() {
  freopen("code.in", "r", stdin);
  freopen("code.out", "w", stdout);
  scanf("%d", &n);
  int tot = (1 << n) - 1, gg = 0;
  for(int i = 0; ; ++i) {
    print(i);
    if(gg + 1 == tot) break;
    print(tot ^ i);
    gg += 2;
  }
  return 0;
}