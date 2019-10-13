#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  srand(time(NULL));
  int n = 10, m = 10;
  ll inf = 1e4;
  cout << n << " " << m << endl;
  for(int i = 1; i <= m; ++i) {
    int l = rand() % n + 1, r = rand() % n + 1;
    if(l > r) swap(l, r);
    ll x = rand() % inf + 1, d = rand() % inf + 1;
    ll y = x + d * (r - l);
    printf("%d %d %lld %lld\n", l, r, x, y);
  } 
  return 0;
}