#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
int a[N], b[N], c[N];

void add() {
  c[0] = max(a[0], b[0]) + 1;
  for(int i = 1; i <= c[0]; ++i)
    c[i] = a[i] + b[i];
  for(int i = 1; i <= c[0]; ++i) {
    c[i + 1] += c[i] / 10;
    c[i] %= 10;
  }
  while(c[0] > 1 && !c[c[0]]) --c[0];
  for(int i = 0; i <= a[0]; ++i)
    b[i] = a[i];
  for(int i = 0; i <= c[0]; ++i)
    a[i] = c[i];
}

int main() {
  a[0] = a[1] = b[0] = b[1] = 1;
  for(int o = 3;; ++o) {
    add();
    if(c[0] >= 1000) {
      printf("%d\n", o);
      return 0;
    }
  }
  return 0;
}