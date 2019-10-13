#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
char lx[N];
set<int> s[30];
set<int> :: iterator sit;

int main() {
  scanf("%s", lx + 1);
  int len = strlen(lx + 1);
  for(int i = 1; i <= len; ++i) {
    s[lx[i] - 'a' + 1].insert(i);
  }
  int q;
  scanf("%d", &q);
  for(int o = 1, tp; o <= q; ++o) {
    scanf("%d", &tp);
    if(tp == 1) {
      int x;
      char ch;
      scanf("%d", &x); cin >> ch;
      s[lx[x] - 'a' + 1].erase(x);
      lx[x] = ch;
      s[lx[x] - 'a' + 1].insert(x);
    } else {
      int l, r;
      scanf("%d%d", &l, &r);
      int ans = 0;
      for(int i = 1; i <= 26; ++i) {
        if(!s[i].size() || *s[i].rbegin() < l) continue;
        sit = s[i].lower_bound(l);
        if(*sit > r) continue;
        ans++;
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}