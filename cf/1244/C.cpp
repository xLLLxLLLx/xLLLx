#include <bits/stdc++.h>
#define ll long long
using namespace std;

void exgcd(ll a,ll b,ll &x,ll &y){
    if(!b) x = 1, y = 0;
    else{
        exgcd(b,a%b,y,x);
        y-=a/b*x;
    }
}

ll gcd(ll a, ll b) {
  return b ? gcd(b, a % b) : a;
}

int main() {
  ll n, p, d, w;
  cin >> n >> p >> w >> d;
  if(p % gcd(w, d)) puts("-1");
  else {
    ll x, y;
    exgcd(w, d, x, y);
    
    printf("%lld %lld\n", x, y);
  }
  return 0;
}