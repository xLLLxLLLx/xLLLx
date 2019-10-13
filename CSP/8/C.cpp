#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10, M = 3e5 + 10;
struct node {
  int id, r, gl, gr; 
} q[N];
struct data {
  int id, r, g;
} a[N];
int d[N], all[M], nm[N];

bool cmp(node A, node B) {
  return A.r > B.r;
}

bool Cmp(data A, data B) {
  return A.r < B.r;
}

bool comp(data A, data B) {
  return A.r > B.r;
}

int tr[M];

int lower(int x) {
  return x & (-x);
}

void upd(int x, int k) {
  for(; x < M; x += lower(x))
    tr[x] += k;
}

int get(int x) {
  int ans = 0;
  for(; x; x -= lower(x))
    ans += tr[x];
  return ans;
}

#define ls x << 1
#define rs x << 1 | 1
int mx[M << 2];

void upd(int x, int l, int r, int L, int w) {
  if(l == r) {
    mx[x] = max(mx[x], w);
    return ;
  }
  int mid = (l + r) >> 1;
  if(L <= mid) upd(ls, l, mid, L, w);
  else upd(rs, mid + 1, r, L, w);
  mx[x] = max(mx[ls], mx[rs]);
}

int get(int x, int l, int r, int L, int R) {
  if(L <= l && r <= R) return mx[x];
  int mid = (l + r) >> 1, ans1 = -1, ans2 = -1;
  if(L <= mid) ans1 = get(ls, l, mid, L, R);
  if(R > mid) ans2 = get(rs, mid + 1, r, L, R);
  return max(ans1, ans2);
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int n, k, res = 0;
    scanf("%d%d", &n, &k);
    for(int i = 1; i <= n; ++i) {
      a[i].id = i;
      scanf("%d", &a[i].r);
    }
    for(int i = 1; i <= n; ++i) {
      scanf("%d", &a[i].g);
      all[++res] = a[i].g;
      all[++res] = a[i].g + k;
      all[++res] = a[i].g - k;
    }
    sort(all + 1, all + 1 + res);
    int tot = unique(all + 1, all + 1 + res) - all - 1;
    int Q;
    scanf("%d", &Q);
    for(int o = 1, x, y; o <= Q; ++o) {
      scanf("%d%d", &x, &y);
      q[o].id = o, q[o].r = max(a[x].r, a[y].r);
      int mn = min(a[x].g, a[y].g), mx = max(a[x].g, a[y].g);
      // [mx - k, mn + k]
      if(mn + k < mx - k) d[o] = -1;
      q[o].gl = lower_bound(all + 1, all + 1 + tot, mx - k) - all;
      q[o].gr = lower_bound(all + 1, all + 1 + tot, mn + k) - all;
    }
    sort(q + 1, q + 1 + Q, cmp);
    sort(a + 1, a + 1 + n, Cmp);
    for(int i = 1; i <= n; ++i) {
      // printf("now = %d\n", i);
      int j = i;
      for(; j <= n && a[j].r == a[i].r; ++j) {
        int pos = lower_bound(all + 1, all + 1 + tot, a[j].g) - all;
        // printf("%d\n", pos);
        upd(pos, 1);
      }
      j--;
      for(int t = i; t <= j; ++t) {
        int L = lower_bound(all + 1, all + 1 + tot, a[t].g - k) - all;
        int R = lower_bound(all + 1, all + 1 + tot, a[t].g + k) - all;
        // printf("id = %d %d %d %d L = %d R = %d\n", a[t].id, a[t].g - k, a[t].g + k, L, R);
        nm[a[t].id] = get(R) - get(L - 1);
      }
      i = j;
    }
    /*for(int i = 1; i <= n; ++i) {
      printf("nm[%d] = %d\n", i, nm[i]);
    }*/
    for(int i = 1; i <= tot * 4; ++i) {
      mx[i] = -1;
    }
    sort(a + 1, a + 1 + n, comp);
    int now = 1;
    for(int i = 1; i <= Q; ++i) {
      while(now <= n && a[now].r >= q[i].r) {
        int pos = lower_bound(all + 1, all + 1 + tot, a[now].g) - all;
        if(nm[a[now].id]) upd(1, 1, tot, pos, nm[a[now].id]);
        now++;
      }
      if(!d[q[i].id]) d[q[i].id] = get(1, 1, tot, q[i].gl, q[i].gr);
    }
    for(int o = 1; o <= Q; ++o) printf("%d\n", d[o]), d[o] = 0;
    for(int i = 0; i < M; ++i) tr[i] = 0;
    // memset(all, 0, sizeof all), memset(nm, 0, sizeof nm);
  }
  return 0;
}