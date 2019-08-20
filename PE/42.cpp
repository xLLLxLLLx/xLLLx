#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
char lx[N];
int flg[N];

int main() {
  scanf("%s", lx + 1);
  for(int i = 1; i <= 100; ++i) {
    flg[i * (i + 1) / 2] = 1;
  }
  int len = strlen(lx + 1), ans = 0;
  for(int i = 1; i <= len; ++i) {
    int pos = 0;
    for(; i <= len && (lx[i] < 'A' || lx[i] > 'Z'); i++);
    for(; lx[i] >= 'A' && lx[i] <= 'Z'; ++i)
      pos += lx[i] - 'A' + 1;
    if(flg[pos]) ans++;
  }
  printf("%d\n", ans);
  return 0;
}