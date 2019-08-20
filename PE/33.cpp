#include <bits/stdc++.h>
using namespace std;

int gcd(int a, int b) {
  return b ? gcd(b, a % b) : a;
}

bool check(int x, int y) {
  int gg = gcd(x, y);
  int s = x / 10, g = x % 10;
  int S = y / 10, G = y % 10;
  x /= gg, y /= gg;
  if(s != G && s != G && g != S && g != G) return false;
  if(s == S && (g < G)) {
    if(x != g) return true;
    if(y != G) return true;
  } else if(s == G && () {
    if(x != g || y != S) return true;
  } else if(g == S) {
    if(x != s || y != G) return true;
  } else {
    if(x != s || y != S) return true;
  }
  return false;
}

int main() {
  int tmp = 1, pos = 1, res = 0;
  for(int i = 10; i <= 99; ++i)
    for(int j = i + 1; j <= 99; ++j) {
      if(check(i, j)) {
        tmp *= i, pos *= j;
        res++;
      }
    }
  printf("%d\n", res);
  int gg = gcd(tmp, pos);
  printf("%d %d\n", res, pos / gg);
  return 0;
}