#include <bits/stdc++.h>
using namespace std;
 
typedef unsigned long long ull;
 
const int M = 100000;
const ull mod = 1ULL << 58;
 
struct element {
  ull coef[5];
 
  element(void) {
    memset(coef, 0, sizeof coef);
  }
  
  void operator += (const element &rhs) {
    for(int i = 0; i < 5; i++) {
      coef[i] += rhs.coef[i];
    }
  }
}a[M], w[10], zero;
 
element operator * (const element &a, const element &b) {
  element c;
  for(int i = 0; i < 5; i++) {
    if(!a.coef[i]) {
      continue;
    }
    for(int j = 0; j < 5; j++) {
      int k = i + j >= 5 ? i + j - 5 : i + j;
      c.coef[k] += a.coef[i] * b.coef[j];
    }
  }
  return c;
}
 
void dft(element* a, int ty) {
  element tmp[M];
  for(int i = 1; i < M; i *= 10) {
    for(int j = 0; j < M; j++) {
      tmp[j] = a[j];
    }
    for(int j = 0; j < M; j += i * 10) {
      for(int k = 0; k < i; k++) {
    for(int x = 0; x < 10; x++) {
      a[j + k + x * i] = zero;
      for(int y = 0; y < 10; y++) {
        a[j + k + x * i] += w[((x * y * ty) % 10 + 10) % 10] * tmp[j + k + y * i];
      }
    }
      }
    }
  }
}
 
element kissme(element x, int y) {
  element c;
  c.coef[0] = 1;
  while(y) {
    if(y & 1) {
      c = c * x;
    }
    x = x * x;
    y >>= 1;
  }
  return c;
}
 
ull kissme(ull x, ull y) {
  ull c = 1;
  while(y) {
    if(y & 1) {
      c = c * x;
    }
    x = x * x;
    y >>= 1;
  }
  return c;
}
 
int n;
 
int main(void) {
  scanf("%d", &n);
  for(int i = 0, x; i < n; i++) {
    scanf("%d", &x);
    a[x].coef[0]++;
  }
  for(int i = 0; i < 10; i++) {
    w[i].coef[i % 5] = (i & 1) ? -1 : 1;
  }
  dft(a, 1);
  for(int i = 0; i < M; i++) {
    a[i] = kissme(a[i], n);
  }
  dft(a, -1);
  ull inv = kissme(125 * 25, (mod >> 1) - 1);
  for(int i = 0; i < n; i++) {
    printf("%llu\n", (((a[i].coef[0] - a[i].coef[1]) * inv) >> 5) % mod);
  }
  return 0;
}