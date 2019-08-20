#include <bits/stdc++.h>
using namespace std;
const int N = 410;
int R[N][N], pw[N][N], ys[N], ans[N], C[N];
int n, m;

void cut(int a[], int x) {
  for(int i = a[0]; i >= 1; --i) {
    a[i - 1] += (a[i] % x) * 10;
    a[i] /= x;
  }
  while(a[0] > 1 && !a[a[0]]) --a[0];
}

void print(int a[]) {
  for(int i = a[0]; i >= 1; --i) {
    printf("%d", a[i]);
  }
  puts("");
}

int c[N];
void add(int a[], int b[]) {
  c[0] = max(a[0], b[0]) + 1;
  for(int i = 1; i <= c[0]; ++i)
    c[i] = a[i] + b[i];
  for(int i = 1; i <= c[0]; ++i) {
    c[i + 1] += c[i] / 10;
    c[i] %= 10;
  }
  while(c[0] > 1 && !c[c[0]]) --c[0];
  for(int i = 0; i <= c[0]; ++i)
    a[i] = c[i];
}

void right() {
  for(int i = 0, t; i < n; ++i) {
    t = R[i][m - 1];
    for(int j = m - 1; j > 0; --j) 
      R[i][j] = R[i][j - 1];
    R[i][0] = t;
  }
}

void down() {
  for(int i = 0, t; i < m; ++i) {
    t = R[n - 1][i];
    for(int j = n - 1; j > 0; --j) 
      R[j][i] = R[j - 1][i];
    R[0][i] = t;
  }
}

int T[N][N];

void rotate() {
  memcpy(T, R, sizeof R);
  for(int i = 0; i < m; ++i) {
    for(int j = n - 1; j > -1; --j) {
      R[i][n - 1 - j] = T[j][i];
    }
  }
  swap(n, m);
}

int cal() {
  int res = 0;
  memset(ys, 0, sizeof ys);
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j)
      C[i * m + j] = R[i][j];
  for(int i = 0, lmt = n * m; i < lmt; ++i) {
    if(!ys[i]) {
      ++res;
      for(int now = i; !ys[now]; ys[now] = 1, now = C[now]);
    }
  }
  // printf("res=%d\n", res);
  return res;
}

int main() {
  freopen("tickets.in", "r", stdin);
  freopen("tickets.out", "w", stdout);
  pw[0][0] = pw[0][1] = 1;
  for(int i = 1; i < N; ++i) {
    add(pw[i], pw[i - 1]), add(pw[i], pw[i - 1]);
  }
  scanf("%d%d", &n, &m);
  for(int i = 0; i < n; ++i)
    for(int j = 0; j < m; ++j)
      R[i][j] = i * m + j;
  for(int i = 0; i < n; ++i) {
    for(int j = 0; j < m; ++j) {
      add(ans, pw[cal()]);
      rotate();
      if(n == m) add(ans, pw[cal()]);
      rotate();
      add(ans, pw[cal()]);
      rotate();
      if(n == m) add(ans, pw[cal()]);
      rotate();
      right();
      // print(ans);
    }
    down();
  }
  int tag = (n == m) ? 2 : 1;
  // print(ans);
  cut(ans, n * m * 2 * tag);
  print(ans);
  return 0;
}