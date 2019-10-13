#include <bits/stdc++.h>
using namespace std;
const int N = 1e5 + 10;
int a[N];

bool cmp(int x, int y) {
  return x > y;
}

int get(int x) {
  int y = x / 100;
  if(x % 100) y++;
  return y * 100;
}

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1, n, m; o <= T; ++o) {
    scanf("%d%d", &n, &m);
    int ans = 0, base = n;
    n *= 100;
    for(int i = 1; i <= m; ++i) {
      scanf("%d", &a[i]);
      a[i] *= 100;
      n -= a[i];
      ans += a[i] / base;
      a[i] %= base;
    }
    sort(a + 1, a + 1 + m, cmp);
    int pos = base / 2 + (base & 1);
    for(int i = 1; i <= n; ++i) {
      if(a[i] >= pos) {
        ans++;
      } else {
        int tmp = pos - a[i];
        tmp = get(tmp);
        if(n >= tmp) {
          n -= tmp;
          a[i] += tmp;
          ans += a[i] / base;
          a[i] %= base;
          if(a[i] >= pos) ans++;
        }
      }
    }
    int lst = get(pos);
    int gg = lst / base, yu = lst % base;
    ans += n / lst * gg + n / lst * (yu >= pos);
    printf("Case #%d: %d\n", o, ans);
  }
  return 0;
}

/*
23 2
1 5 
*/