#include <bits/stdc++.h>
using namespace std;
int nm[10];

void jl(int x) {
  memset(nm, 0, sizeof nm);
  for(; x; x /= 10) {
    nm[x % 10]++;
  }
}

int c[10];
bool check(int x) {
  memset(c, 0, sizeof c);
  for(; x; x /= 10) {
    c[x % 10]++;
  }
  for(int i = 0; i <= 9; ++i)
    if(c[i] != nm[i]) {
      return false;
    }
  return true;
}

int main() {
  for(int i = 1; ; ++i) {
    jl(i);
    int flg = 1;
    for(int j = 1; j <= 6; ++j) {
      if(!check(i * j)) {
        flg = 0;
        break;
      }
    }
    if(flg) {
      printf("%d\n", i);
      return 0;
    }
  }
  return 0;
}