#include <bits/stdc++.h>
using namespace std;
const int N = 110;
int a[N][N], c[N][N], r[N], b[N], d[N], w[N];

int main() {
  int T;
  scanf("%d", &T);
  for(int o = 1; o <= T; ++o) {
    int n, m, h, v, tot = 0;
    scanf("%d%d%d%d", &n, &m, &h, &v);
    memset(r, 0, sizeof r);
    for(int i = 1; i <= n; ++i)
      for(int j = 1; j <= m; ++j) {
        char ch;
        cin >> ch;
        if(ch == '@') a[i][j] = 1;
        else a[i][j] = 0;
        tot += a[i][j], r[j] += a[i][j];
      }
    printf("Case #%d: ", o);
    if(tot % ((h + 1) * (v + 1))) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    tot /= ((h + 1) * (v + 1));
    int flg = 1, res = 0;
    b[res] = 0;
    for(int i = 1; i <= m; ++i) {
      int now = 0;
      for(int j = i; j <= m; ++j) {
        now += r[j];
        if(now == tot * (h + 1)) {
          i = j;
          break;
        }
      }
      if(now != tot * (h + 1)){
        flg = 0;
        break;
      } else {
        b[++res] = i;
      }
    }
    if(!flg) {
      printf("IMPOSSIBLE\n");
      continue;
    }
    // puts("");
    memset(c, 0, sizeof c);
    for(int i = 0; i <= v; ++i) {
      int l = b[i] + 1, r = b[i + 1];
      for(int j = 1; j <= n; ++j)
        for(int k = l; k <= r; ++k)
          c[j][i + 1] += a[j][k];
    }
    int cnt = 0;
    for(int i = 1; i <= n; ++i) {
      if(cnt >= h + 1) break;
      ++cnt;
      memset(w, 0, sizeof w);
      int num = 0;
      for(int j = i; j <= n; ++j) {
        for(int k = 1; k <= v + 1; ++k) {
          w[k] += c[j][k];
        }
        num = 0;
        for(int k = 1; k <= v + 1; ++k)
          num += (w[k] == tot);
        if(num == v + 1) {
          i = j;
          break;
        }
      }
      if(num != v + 1) {
        flg = 0;
        break;
      }
      for(int j = 1; j <= v + 1; ++j)
        if(w[j] != tot) {
          flg = 0;
          break;
        }
    }
    if(!flg) printf("IMPOSSIBLE\n");
    else printf("POSSIBLE\n");
  }
  return 0;
}