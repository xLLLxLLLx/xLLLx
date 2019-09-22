#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int LOG = 62;
typedef pair<int, int> P;
vector<P> g;

int main() {
  ll w;
  scanf("%lld", &w);
  int maxn = 0;
  for(int i = 0; i <= LOG; ++i) {
    if((w >> i) & 1) {
      maxn = max(maxn, i);
    }
  }
  for(int i = 1; i <= maxn + 2; ++i)
    for(int j = i + 1; j <= maxn + 2; ++j) {
      g.push_back(P(i, j));
    }
  for(int i = 0; i <= LOG; ++i) {
    if((w >> i) & 1) {
      g.push_back(P(i + 2, maxn + 3));
    }
  }
  printf("%d %d\n", maxn + 3, g.size());
  for(int i = 0; i < g.size(); ++i) {
    printf("%d %d\n", g[i].first, g[i].second);
  }
  return 0;
}