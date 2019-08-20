#include <bits/stdc++.h>
using namespace std;
const int N = 210;
struct data {
  int a[N];
} f[N][N][2], xs[N][N];
int sz[N], nm[N];
char lx[N];

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

void cut() {
  for(int i = sz[0]; i >= 1; --i) {
    sz[i - 1] += (sz[i] % 2) * 10;
    sz[i] /= 2;
  }
  while(sz[0] > 1 && !sz[sz[0]]) --sz[0];
}



void pre() {
  sz[0] = strlen(lx + 1);
  for(int i = 1; i <= sz[0]; ++i)
    sz[sz[0] - i + 1] = lx[i] - '0';
  for(; sz[0] > 1 || (sz[0] == 1 && sz[1]); cut())
    nm[++nm[0]] = sz[1] & 1;
  for(int i = nm[0]; i >= 1; --i)
    printf("%d", nm[i]);
  puts("");
}

void print(int a[]) {
  for(int i = a[0]; i >= 1; --i)
    printf("%d", a[i]);
  puts("");
}

int c[N];
void mul(int a[], int b[]) {
  c[0] = a[0] + b[0] + 1;
  for(int i = 1; i <= a[0]; ++i)
    for(int j = 1; j <= b[0]; ++j)
      c[i + j - 1] = a[i] * b[i];
  for(int i = 1; i <= c[0]; ++i) {
    c[i + 1] += c[i] / 10;
    c[i] %= 10;
  }
  while(c[0] > 1 && !c[c[0]]) --c[0];
}

int ans[N];

int main() {
  // freopen("digit.in", "r", stdin);
  // freopen("digit.out", "w", stdout);
  scanf("%s", lx + 1);
  pre();
  f[0][nm[1]].a[0] = f[0][nm[1]].a[1] = 1;
  int now = 0;
  for(int i = 1; i <= nm[0]; ++i) {
    now ^= 1;
    if(nm[i + 1]) {
      for(int j = 0; j <= i; ++j) {
        add(f[now][0].a, f[now ^ 1][j]);
        mul(xs[now ^ i][j], f[now ^ 1][j]);
        add(f[now][1].a, c);
      }
    } else {
      for(int j = 0; j <= i; ++j) {
        add(f[now][j + 1].a, f[now ^ 1][j]);
      }
    }
  }
  for(int i = 1; i <= nm[0]; ++i)
    add(ans, f[now][i].a);
  print(ans);
  return 0;
}