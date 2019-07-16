#include <bits/stdc++.h>
using namespace std;
const int N = 2e6 + 10;
struct node {
  int x, y;
};
vector<int> g;
vector<node> fir;
int n, m1, m2, t, tot;
int all[N], f[N][2], z[N][2], ys[N][2], rev[N][2];

int get(int x) {
  return lower_bound(all + 1, all + 1 + tot, x) - all;
}

bool cmp(node A, node B) {
  return A.x < B.x;
}

void print(int x) {
  printf("Yes\n");
  int tmp = 2e9;
  for(int i = tot; i; --i) {
    if(rev[i][x]) {
      x ^= 1;
      g.push_back(all[i]);
    }
    int d = all[i] - all[i - 1];
    if(f[i - 1][x] + d > f[i][x]) {
      int pos = min(tmp - t, all[i] - 1);
      tmp = pos;
      fir.push_back((node){pos, x + 1});
    }
  }
  /*output*/
  if(x) g.push_back(0);
  sort(g.begin(), g.end());
  sort(g.begin(), g.end());
  printf("%d\n", (int)g.size());
  for(int i = 0; i < g.size(); ++i) {
    printf("%d ", g[i]);
  }
  puts("");
  sort(fir.begin(), fir.end(), cmp);
  printf("%d\n", (int)fir.size());
  for(int i = 0; i < fir.size(); ++i) {
    printf("%d %d\n", fir[i].x, fir[i].y);
  }
}

int main() {
  scanf("%d%d%d%d", &n, &m1, &m2, &t);
  int cnt = 0;
  for(int i = 1; i <= m1; ++i) {
    scanf("%d", &z[i][0]);
    all[++cnt] = z[i][0], all[++cnt] = z[i][0] + 1;
  }
  for(int i = 1; i <= m2; ++i) {
    scanf("%d", &z[i][1]);
    all[++cnt] = z[i][1], all[++cnt] = z[i][1] + 1;
  }
  sort(all + 1, all + 1 + cnt);
  tot = unique(all + 1, all + 1 + cnt) - all - 1;
  for(int i = 1; i <= m1; ++i) {
    z[i][0] = get(z[i][0]);
    ys[z[i][0]][0] = 1;
  }
  for(int i = 1; i <= m2; ++i) {
    z[i][1] = get(z[i][1]);
    ys[z[i][1]][1] = 1;
  }
  memset(f, -1, sizeof f);
  f[0][0] = f[0][1] = 0;
  for(int i = 1; i <= tot; ++i) {
    int d = all[i] - all[i - 1];
    for(int j = 0; j < 2; ++j) {
      if(f[i - 1][j] == -1) {
        continue;
      }
      if(ys[i][j]) {
        if(f[i - 1][j] + d - 1 >= t && f[i - 1][j] + d - t > f[i][j]) {
          f[i][j] = f[i - 1][j] + d - t;
          rev[i][j] = 0;
        }
      } else {
        if(f[i - 1][j] + d > f[i][j]) {
          f[i][j] = f[i - 1][j] + d;
          rev[i][j] = 0;
        }
      }
    }
    if(!ys[i][1] && ~f[i][0] && min(f[i][0], t) > f[i][1]) {
      f[i][1] = min(f[i][0], t);
      rev[i][1] = 1;
    }
    if(!ys[i][0] && ~f[i][1] && min(f[i][1], t) > f[i][0]) {
      f[i][0] = min(f[i][1], t);
      rev[i][0] = 1;
    }
  }
  // for(int i = 1; i <= tot; ++i) {
  //   for(int j = 0; j < 2; ++j) {
  //     printf("f[%d][%d] = %d\n", i, j, f[i][j]);
  //   }
  // }
  if(~f[tot][0]) print(0);
  else if(~f[tot][1]) print(1);
  else printf("No\n");
  return 0;
}