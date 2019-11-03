#include <bits/stdc++.h>
using namespace std;
const int N = 5010;
struct data {
  int x, y;
} a[N];

bool cmp(data A, data B) {
  return 1ll * A.x * A.y < 1ll * B.x * B.y;
}

int d[N], c[N];

bool check() {
  if(d[0] < c[0]) return false;
  for(int i = c[0]; i >= 1; --i)
    if(c[i] > d[i]) return false;
    else if(c[i] < d[i]) return true;
  return true;
}

void gai() {
  if(!check()) {
    for(int i = 0; i <= c[0]; ++i)
      d[i] = c[i];
  }
}

void jw(int a[]) {
  while(a[a[0]] >= 10) {
    a[a[0] + 1] += a[a[0]] / 10;
    a[a[0]] %= 10;
    a[0]++;
  }
}

void div(int a[], int x) {
  memset(c, 0, sizeof c);
  int now = 0;
  c[0] = a[0];
  for(int i = a[0]; i >= 1; --i) {
    now = now * 10 + a[i];
    c[i] = now / x;
    now %= x;
  }
  while(c[0] > 1 && !c[c[0]]) --c[0];
  // for(int i = c[0]; i >= 1; --i)
  //   printf("%d", c[i]);
  // puts("");
  // puts("div!");
  gai();
}

int s[N];
void mul(int a[], int x) {
  memset(c, 0, sizeof c);
  c[0] = a[0] + 1;
  for(int i = 1; i <= a[0]; ++i) {
    c[i] += a[i] * x;
    c[i + 1] += c[i] / 10;
    c[i] %= 10;
  }
  while(c[0] > 1 && !c[c[0]]) --c[0];
  jw(c);
  // puts("");
  for(int i = 0; i <= c[0]; ++i)
    s[i] = c[i];
  // for(int i = s[0]; i >= 1; --i)
  //   printf("%d", s[i]);
  // puts("");
  // puts("mul!");
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 0; i <= n; ++i) {
    scanf("%d%d", &a[i].x, &a[i].y);
  }
  sort(a + 1, a + 1 + n, cmp);
  s[s[0] = 1] = a[0].x, jw(s);
  for(int i = 1; i <= n; ++i) {
    // printf("x = %d y = %d\n", a[i].x, a[i].y);
    div(s, a[i].y);
    mul(s, a[i].x);
  }
  // printf("d[0] = %d\n", d[0]);
  for(int i = d[0]; i >= 1; --i)
    printf("%d", d[i]);
  puts("");
  return 0;
}