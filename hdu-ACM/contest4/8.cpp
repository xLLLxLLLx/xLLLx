#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int sz = 0, tot;
int a[N], all[N];
int lson[N * 40], rson[N * 40], rt[N * 40], sum[N * 40];

void init() {
  sz = 0;
}

void build(int &nw,int l,int r){
  nw=++sz,sum[nw]=0,lson[nw]=0,rson[nw]=0;
  if(l==r) return ;
  int mid=(l+r)>>1;
  build(lson[nw],l,mid),build(rson[nw],mid+1,r);
}

void change(int old,int &nw,int L,int l,int r,int k){
  nw=++sz;
  sum[nw]=sum[old]+k,lson[nw]=lson[old],rson[nw]=rson[old];
  if(l==r) return ;
  int mid=(l+r)>>1;
  if(L<=mid) change(lson[nw],lson[nw],L,l,mid,k);
  else change(rson[nw],rson[nw],L,mid+1,r,k);
}

int find(int qq,int hq,int l,int r,int L, int R){
  if(L <= l && r <= R) return sum[hq] - sum[qq];
  int mid = (l + r) >> 1, ans1 = 0, ans2 = 0;
  if(L <= mid) ans1 = find(lson[qq], lson[hq], l, mid, L, R);
  if(R > mid) ans2 = find(rson[qq], rson[hq], mid + 1, r, L, R);
  return ans1 + ans2;
}

int findl(int x) {
  int l = 1, r = tot, ans = 1;
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(all[mid] >= x) ans = mid, r = mid - 1;
    else l = mid + 1;
  }
  return ans;
}

int findr(int x) {
  int l = 1, r = tot, ans = tot;
  while(l <= r) {
    int mid = (l + r) >> 1;
    if(all[mid] <= x) ans = mid, l = mid + 1;
    else r = mid - 1;
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    init();
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) {
      scanf("%d", &a[i]);
      all[i] = a[i];
    }
    sort(all + 1, all + 1 + n);
    tot = unique(all + 1, all + 1 + n) - all - 1;
    build(rt[0], 1, tot);
    for(int i = 1; i <= n; ++i) {
      a[i] = lower_bound(all + 1, all + 1 + tot, a[i]) - all;
      change(rt[i - 1], rt[i], a[i], 1, tot, 1);
    }
    int ans = 0;
    for(int i = 1; i <= m; ++i) {
      int L, R, p, k;
      scanf("%d%d%d%d", &L, &R, &p, &k);
      L ^= ans, R ^= ans, p ^= ans, k ^= ans;
      int l = 0, r = 1000000;
      while(l <= r) {
        int mid = (l + r) >> 1;
        int nl = max(0, p - mid), nr = min(p + mid, all[tot]);
        nl = findl(nl), nr = findr(nr);
        if(find(rt[L - 1], rt[R], 1, tot, nl, nr) >= k) ans = mid, r = mid - 1;
        else l = mid + 1;
      }
      printf("%d\n", ans);
    }
  }
  return 0;
}