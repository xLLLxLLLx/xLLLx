#include <bits/stdc++.h>
using namespace std;
const int N = 55, M = (1 << 20), K = 21;
int len[N], cnt[M];
char lx[N][K];
vector<int> g;
double f[M];

void init() {
  for(int i = 0; i < M; ++i) {
    cnt[i] = cnt[i >> 1] + (i & 1);
    // assert(cnt[i] <= 20);
  }
}

int n, mx;

bool check(int x, int y) {
  for(int i = 1; i <= n; ++i) {
    if(i == x) continue;
    int flg = 1;
    for(int j = 0; j < mx; ++j) {
      if((y >> j) & 1) {
        if(lx[i][j] != lx[x][j]) {
          flg = 0;
          break;
        }
      }
    }
    if(flg) return false;
  }
  return true;
}

int main() {
  init();
  scanf("%d", &n);
  for(int i = 1; i <= n; ++i) {
    scanf("%s", lx[i]);
  }
  mx = strlen(lx[1]);
  int tot = (1 << mx);
  double ans = 0;
  for(int i = 1; i <= n; ++i) {
    // printf("now = %d\n", i);
    memset(f, 0, sizeof f);
    f[0] = 1;
    for(int j = 0; j < tot; ++j) {
      if(!check(i, j)) {
        if(!f[j]) continue;
        for(int k = 0; k < mx; ++k) {
          if((j >> k) & 1) continue;
          f[j | (1 << k)] += f[j] / double(mx - cnt[j]);
        }
      } else g.push_back(j);
    } 
    double pos = 0;
    for(int j = 0; j < (int)g.size(); ++j) {
      // printf("%d %lf %d\n", g[j], f[g[j]], cnt[g[j]]);
      pos += f[g[j]] * cnt[g[j]];
    }
    ans += pos;
    // printf("%lf\n", pos);
    g.clear();
  }
  ans /= (double)n;
  printf("%.12f\n", ans);
  return 0;
}