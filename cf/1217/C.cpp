#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 2e5 + 10, LOG = 20;
int a[N], st[N][LOG + 1];
char lx[N];

int get(int l, int r) {
  if(r < l) return 0;
  int k = (int)(log(double(r - l + 1)) / log(2.0));
  return max(st[l][k], st[r - (1 << k) + 1][k]);
}

int main() {
  int T;
  cin >> T;
  for(int o = 1; o <= T; ++o) {
    scanf("%s", lx + 1);
    int n = strlen(lx + 1);
    for(int i = 1; i <= n; ++i) {
      a[i] = lx[i] - '0';
    }
    // puts("xxxx");
    for(int i = 1; i <= n; ++i) st[i][0] = a[i];
    for(int j = 1; j <= LOG; ++j)
      for(int i = 1; i <= n; ++i) {
        if(i + (1 << j) > n + 1) continue;
        st[i][j] = max(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
      }
    int res = 0;
    for(int i = 1; i <= n; ++i) {
      // printf("%d\n", i);
      if(a[i]) {
        int pos = 1;
        res++;
        for(int j = i + 1; j <= n; ++j) {
          pos = pos * 2 + a[j];
          if(pos > j) break;
          int L = j - pos + 1;
          if(!get(L, i - 1)) res++;
        }
      }
    }
    printf("%d\n", res);
  }
  return 0;
}