#include <bits/stdc++.h>
using namespace std;
const int N = 55;
int dx[4] = {0, 1, 0, 1};
int dy[4] = {1, 0, 0, 1};
struct data {
  int x, y;
}b[N * N];
int res = 0, a[N][N], vs[N][N];

void fail() {
  puts("-1");
  exit(0);
}

int main() {
  int n, m;
  cin >> n >> m;
  for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= m; ++j)
      scanf("%d", &a[i][j]);
  for(int i = 1; i <= n; ++i) 
    for(int j = 1; j <= m; ++j) {
      if(a[i][j]) {
        int flg = 1;
        for(int t = 0; t < 4; ++t) {
          int xx = i + dx[t], yy = j + dy[t];
          if(xx > n || xx <= 0 || yy > m || yy <= 0) flg = 0;
          if(!a[xx][yy]) flg = 0;
        }
        if(flg) {
          for(int t = 0; t < 4; ++t) {
            int xx = i + dx[t], yy = j + dy[t];
            vs[xx][yy] = 1;
          }
          b[++res] = (data){i, j};
        }
      }
    }
  for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= m; ++j)
      if(a[i][j] != vs[i][j]) fail();
  printf("%d\n", res);
  for(int i = 1; i <= res; ++i)
    printf("%d %d\n", b[i].x, b[i].y);
  return 0;
}