#include <bits/stdc++.h>
using namespace std;
const int N= 1010;
struct data {
    int id, w;
}a[N];
int nm[N];
 
bool cmp(data A, data B) {
    return A.w == B.w ? A.id < B.id : A.w < B.w;
}
 
bool comp(int x, int y) {
    return x > y;
}
 
int main() {
  int f, m, goal;
  cin >> f >> m >> goal;
  int cnt = 0;
  for(int i = 1; i <= f; ++i) {
    for(int j = 1; j <= m; ++j) {
      int x; scanf("%d", &x);
      a[++cnt].w = x;
      a[cnt].id = i;
    }
  }
  sort(a + 1, a + 1 + cnt, cmp);
  int mid = cnt / 2 + (cnt & 1);
  int ed = -1, flg = 0;
  for(int i = 1; i <= cnt; ++i) {
    if(a[i].w <= goal) ed = i;
    if(a[i].w == goal) flg = 1;
  }
  int be = -1;
  for(int i = cnt; i >= 1; --i) {
    if(a[i].w >= goal) be = i;
  }
  if(flg) {
    if(be <= mid && mid <= ed) return printf("0 0\n"), 0;
    else {
      if(mid < be) {
        for(int i = 1; i < be; ++i) {
          nm[a[i].id]++;
        }
        sort(nm + 1, nm + 1 + f, comp);
        int pos = be - mid, ans = 0;
        for(int i = 1; i <= f; ++i) {
          pos -= nm[i];
          ans++;
          if(pos <= 0) break;
        }
        printf("%d %d\n", ans, be - mid);
      } else {
        for(int i = ed + 1; i <= cnt; ++i) {
          nm[a[i].id]++;
        }
        sort(nm + 1, nm + 1 + f, comp);
        int pos = mid - ed, ans = 0;
        for(int i = 1; i <= f; ++i) {
          pos -= nm[i];
          ans++;
          if(pos <= 0) break;
        }
        printf("%d %d\n", ans, mid - ed);
      }
    }
  } else {
  	swap(be, ed);
    if(ed == -1 || mid <= be) {
      for(int i = 1; i <= be; ++i) {
        nm[a[i].id]++;
      }
      sort(nm + 1, nm + 1 + f, comp);
      int pos = be - mid + 1, ans = 0;
      for(int i = 1; i <= f; ++i) {
        pos -= nm[i];
        ans++;
        if(pos <= 0) break;
      }
      printf("%d %d\n", ans, be - mid + 1);
    } else {
      for(int i = ed; i <= cnt; ++i) {
        nm[a[i].id]++;
      }
      sort(nm + 1, nm + 1 + f, comp);
      int pos = mid - ed + 1, ans = 0;
      for(int i = 1; i <= f; ++i) {
        pos -= nm[i];
        ans++;
        if(pos <= 0) break;
      }
      printf("%d %d\n", ans, mid - ed + 1);
    }
  }
  return 0;
}