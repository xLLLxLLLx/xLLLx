#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int a[N];

int ask() {
  printf("? ");fflush(stdout);
  for(int i = 0; i < 100; ++i) {
    printf("%d ", a[i]);fflush(stdout);
  }
  printf("\n");fflush(stdout);
  int x;
  scanf("%d", &x);
  return x;
}

int main() {
  int pos = (1 << 7) - 1, tot = (1 << 14) - 1;
  int tmp = tot ^ pos;
  for(int i = 0; i < 100; ++i) {
    a[i] = i;
  }
  int ans = ask() & tmp;
  for(int i = 0; i < 100; ++i) {
    a[i] = tmp ^ (i * (1 << 7));
  }
  ans += ask() & pos;
  printf("! %d\n", ans); fflush(stdout);
  return 0;
}