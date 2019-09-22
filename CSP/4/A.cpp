#include <bits/stdc++.h>
#define ll long long
using namespace std;
const int LOG = 60;
typedef pair<int, int> P;
vector<P> q;
int a[LOG];

int main() {
  ll w;
  cin >> w;
  if(w == 1) {
    printf("2 1\n1 2\n");
    return 0;
  }
  int n, m;
  for(int i = LOG; i >= 0; --i) {
    if((w >> i) & 1) {
      if(!n) n = i;
      a[LOG] = 1;
    }
  }
  for(int i = 1; i <= n; ++i) {
    int pos = i * 3 - 2;
    q.push_back(P(pos, pos + 1)), q.push_back(P(pos, pos + 2));
    q.push_back(P(pos + 1, pos + 3)), q.push_back(P(pos + 2, pos + 3));
  }
  for(int i = 0; i <= n; ++i) {
    if(a[i]) {
      q.push_back(P(1, (n + 1 - i) * 3 - 2));
    }
  }
  printf("%d %d\n", (n + 1) * 3 - 2, q.size());
  for(int i = 0; i < q.size(); ++i) {
    printf("%d %d\n", q[i].first, q[i].second);
  }
  return 0;
}