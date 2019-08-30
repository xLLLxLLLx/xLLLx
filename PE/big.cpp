#include <bits/stdc++.h>
using namespace std;
const int N = 1010;
char lx[N], ll[N];
int a[N], b[N], c[N];

int main() {
  scanf("%s%s", lx + 1, ll + 1);
  a[0] = strlen(lx + 1);
  b[0] = strlen(ll + 1);
  for(int i = 1; i <= a[0]; ++i)
    a[a[0] - i + 1] = lx[i] - '0';
  for(int i = 1; i <= b[0]; ++i)
    b[b[0] - i + 1] = ll[i] - '0';
  c[0] = max(a[0], b[0]) + 1;
  for(int i = 1; i <= c[0]; ++i)
    c[i] = a[i] + b[i];
  for(int i = 1; i <= c[0]; ++i) {
    c[i + 1] += c[i] / 10;
    c[i] %= 10;
  }
  while(c[0] > 1 && !c[c[0]]) --c[0];
  for(int i = c[0]; i >= 1; --i)
    printf("%d", c[i]);
  puts("");
  return 0;
}