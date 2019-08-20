#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
int a[N];

int main() {
  int n;
  scanf("%d", &n);
  if(n & 1) {
    printf("YES\n");
    for(int i = 1; i <= n; ++i) {
      if(i & 1)a[i] = i * 2 - 1, a[i + n] = i * 2;
      else a[i] = i * 2, a[i + n] = i * 2 - 1;
    }
    for(int i = 1; i <= 2 * n; ++i) 
      printf("%d ", a[i]);
    puts("");
  } else {
    printf("NO\n");
  }
  return 0;
}