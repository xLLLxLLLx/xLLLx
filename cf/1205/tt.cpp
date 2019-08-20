#include <bits/stdc++.h>
#define ll long long
using namespace std;

int main() {
  srand(time(NULL));
  int n = 100000;
  cout<<n<<endl;
  for(int i = 1; i <= 55; ++i) {
    printf("%lld %lld ", (1ll << i));
  }
  for(int i = 1; i <= n - 110; ++i)
    printf("0 ");
  return 0;
}