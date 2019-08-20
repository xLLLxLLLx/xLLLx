#include <bits/stdc++.h>
using namespace std;
const int N = 1e6 + 10;
int nm[N], add[N];

void insert(int x) {
  add[0] = 0;
  for(; x; x /= 10) add[++add[0]] = x % 10;
  reverse(add + 1, add + 1 + add[0]);
  for(int i = 1; i <= add[0]; ++i)
    nm[++nm[0]] = add[i];
}

int main() {
  for(int i = 1; i <= 1000000; ++i) {
    insert(i);
    if(nm[0] >= 1000000) break;
  }
  int pos = 1, pw = 1;
  for(int i = 1; i <= 6; ++i) {
    pos = pos * nm[pw];
    pw = pw * 10;
  }
  printf("%d\n", pos);
  return 0;
}