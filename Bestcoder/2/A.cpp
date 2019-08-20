#include <bits/stdc++.h>
using namespace std;
int n;
vector<int> g;

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    g.clear();
    scanf("%d", &n);
    int pos = n, tmp = 0;
    for(; pos; pos /= 10) tmp += pos % 10;
    int m = sqrt(n);
    for(int i = 1; i <= m; ++i) {
      if(n % i == 0) {
        if(tmp % i == 0) g.push_back(i);
        if(i * i != n) {
          if(tmp % (n / i) == 0) g.push_back(n / i);
        }
      }
    }
    sort(g.begin(), g.end());
    printf("%d\n", (int)g.size());
    for(int i = 0; i < (int)g.size(); ++i) {
      if(i) printf(" ");
      printf("%d", g[i]);
    }
    puts("");
  }
  return 0;
}