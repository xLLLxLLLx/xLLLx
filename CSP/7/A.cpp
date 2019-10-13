#include <bits/stdc++.h>
using namespace std;
const int N = 2e5 + 10;
struct data {
  int tp, x, y;
} a[N];
char lx[10];
int all[N];
multiset<int> s[N];

#define ls x << 1
#define rs x << 1 | 1

int mx[N << 2], inf = 1e9 + 1;
void upd(int x, int l, int r, int L) {
  if(l == r) {
    if(s[l].size()) mx[x] = *s[l].rbegin();
    else mx[x] = -inf;
    return ;
  }
  int mid = (l + r) >> 1;
  if(L <= mid) upd(ls, l, mid, L);
  else upd(rs, mid + 1, r, L);
  mx[x] = max(mx[ls], mx[rs]);
}

int find(int x, int l, int r, int L, int y) {
  if(r <= L || mx[x] <= y) return -1;
  if(l == r) return l;
  int mid = (l + r) >> 1;
  int pos = find(ls, l, mid, L, y);
  if(pos == -1) return find(rs, mid + 1, r, L, y);
  else return pos;
}

int main() {
  int n;
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%s", lx + 1);
    scanf("%d%d", &a[i].x, &a[i].y);
    all[i] = a[i].x;
    if(lx[1] == 'a') a[i].tp = 1;
    else if(lx[1] == 'r') a[i].tp = 2;
    else a[i].tp = 3;
  }
  sort(all + 1, all + 1 + n);
  int m = unique(all + 1, all + 1 + n) - all - 1;
  for(int i = 1; i <= m * 4; ++i)
    mx[i] = -inf;
  for(int i = 1; i <= n; ++i) {
    a[i].x = lower_bound(all + 1, all + 1 + m, a[i].x) - all;
    if(a[i].tp == 1) {
      s[a[i].x].insert(a[i].y);
      upd(1, 1, m, a[i].x);
    } else if(a[i].tp == 2) {
      s[a[i].x].erase(s[a[i].x].find(a[i].y));
      upd(1, 1, m, a[i].x);
    } else {
      int x = find(1, 1, m, a[i].x, a[i].y);
      if(x == -1) puts("-1");
      else {
        int y = *s[x].upper_bound(a[i].y);
        printf("%d %d\n", all[x], y);
      }
    }
  }
  return 0;
}