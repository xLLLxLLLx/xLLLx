#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int N = 5e5 + 10;
priority_queue<ll, vector<ll>, greater<ll> >q;

template <class T>
void read(T & x) {
  char ch = getchar(); x = 0;
  for(; ch < '0' || ch > '9'; ch = getchar()) ;
  for(; ch >= '0' && ch <= '9'; ch = getchar()) x = (x << 1) + (x << 3) + (ch ^ 48);
}

int main() {
  freopen("huffman.in", "r", stdin);
  freopen("huffman.out", "w", stdout);
  int n;
  read(n);
  for(int i = 1; i <= n; ++i) {
    ll x;
    read(x);
    q.push(x);
  }
  ll ans = 0;
  while(q.size() > 1) {
    ll pos = q.top(); q.pop();
    ll tmp = q.top(); q.pop();
    ans += pos + tmp;
    q.push(pos + tmp);
  }
  printf("%lld\n", ans);
  return 0;
}