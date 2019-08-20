#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2100;
int a[N];
int f[N][N];

void add(int a[], int b[]) {
  a[0] = max(a[0], b[0]) + 1;
  for(int i = 1; i <= a[0]; ++i)
    a[i] += b[i];
  for(int i = 1; i <= a[0]; ++i) {
    a[i + 1] += a[i] / 10;
    a[i] %= 10;
  }
  while(a[0] > 1 && !a[a[0]]) --a[0];
}

void print(int a[]) {
  for(int i = a[0]; i >= 1; --i)
    printf("%d", a[i]);
  puts("");
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  f[0][0] = f[0][1] = 1;
  for(int j = 1; j <= n; ++j) 
  for(int i = 1; i <= m; ++i) {
      if(i < a[j]) continue;
      add(f[i], f[i - a[j]]);
    }
  print(f[m]);
  return 0;
}