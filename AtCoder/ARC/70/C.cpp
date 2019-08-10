#include <bits/stdc++.h>
using namespace std;

int main() {
  int n;
  cin >> n;
  int sum = 0, i = 1;
  for(; sum < n; ++i) {
    sum += i;
  }
  printf("%d\n", i - 1);
  return 0;
}
