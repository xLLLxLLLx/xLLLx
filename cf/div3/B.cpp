#include <bits/stdc++.h>
using namespace std;
const int N = 11, M = 2510, Mask = (1 << 10), mod = 1e9 + 7;
struct data {
  int nt, to;
} a[M << 1];
int head[N], cnt = 0;
//dp[be_col][now_col][col_ed][col_mask]
//f[be][ed][point_mask]
int f[N][N][Mask], F[N][N][N], dp[N][N][N][Mask], col[N], len[N], all[N], g[N][N], ys[N];

void add(int x, int y) {
  a[++cnt].to = y;
  a[cnt].nt = head[x];
  head[x] = cnt;
}

void Add(int &x, int y) {
  x = (x + y) % mod;
}

int mul(int x, int y) {
  return 1ll * x * y % mod;
}

int n, m, tc, y[M];

void init() {
  scanf("%d%d", &n, &m);
  for(int i = 1; i <= n; ++i) {
    scanf("%d", &col[i]);
    all[i] = col[i];
  }
  for(int i = 1; i <= m; ++i) {
    scanf("%d", &y[i]);
    y[i]++;
  }
  for(int i = 1, x; i <= m; ++i) {
    scanf("%d", &x);
    x++;
    add(x, y[i]), add(y[i], x);
  }
  sort(all + 1, all + n + 1);
  tc = unique(all + 1, all + 1 + n) - all - 1;
  for(int i = 1; i <= n; ++i) {
    col[i] = lower_bound(all + 1, all + 1 + tc, col[i]) - all - 1;
    g[col[i]][++len[col[i]]] = i;
  }
  for(int i = 0; i < tc; ++i) {
    sort(g[i] + 1, g[i] + 1 + len[i]);
    for(int j = 1; j <= len[i]; ++j)
      ys[g[i][j]] = lower_bound(g[i] + 1, g[i] + 1 + len[i], g[i][j]) - g[i] - 1;
  }
}

int main() {
  init();
  memset(dp, -1, sizeof dp);
  for(int o = 0; o < tc; ++o) {
    memset(f, -1, sizeof f);
    for(int i = 0; i < len[o]; ++i) {
      f[i][i][1 << i] = 1;
    }   
    for(int k = 0; k < (1 << len[o]); ++k)
    for(int i = 0; i < len[o]; ++i) 
      for(int j = 0; j < len[o]; ++j)  {
        //f[i][j][k]
        if(~f[i][j][k]) {
          int ed = g[o][j + 1];
          for(int t = head[ed]; t; t = a[t].nt) {
            int to = a[t].to;
            if(col[to] != o ||  ((k >> ys[to]) & 1)) continue;
            if(f[i][ys[to]][k | (1 << ys[to])] == -1) f[i][ys[to]][k | (1 << ys[to])] = 0;
            Add(f[i][ys[to]][k | (1 << ys[to])], f[i][j][k]);
          }
        }
      }
    for(int i = 0; i < len[o]; ++i)
      for(int j = 0; j < len[o]; ++j) {
        if(f[i][j][(1 << len[o]) - 1] == -1) continue;
        if(dp[o][o][j][1 << o] == -1) dp[o][o][j][1 << o] = 0;
        F[o][i][j] = f[i][j][(1 << len[o]) - 1];
        Add(dp[o][o][j][1 << o], F[o][i][j]); 
      }
  }
  for(int mk = 1; mk < (1 << tc); ++mk)for(int i = 0; i < tc; ++i) for(int j = 0; j < tc; ++j) for(int k = 0; k < len[j]; ++k)  {
      //dp[i][j][k][mk]
      if(~dp[i][j][k][mk]) {
        int K = g[j][k + 1];  //before ed
        for(int o = head[K]; o; o = a[o].nt) {
          int to = a[o].to, nc = col[to]; // K -> to, to -> ed
          if((mk >> nc) & 1) continue;  
          //add nc
          for(int ed = 0; ed < len[nc]; ++ed) {
            if(~F[nc][ys[to]][ed]) {
              if(dp[i][nc][ed][mk | (1 << nc)] == -1) dp[i][nc][ed][mk | (1 << nc)] = 0;
              Add(dp[i][nc][ed][mk | (1 << nc)], mul(dp[i][j][k][mk], F[nc][ys[to]][ed]));
            }
          }
        }
      }
    }
/*  for(int i = 0; i < tc; ++i) 
    for(int j = 0; j < tc; ++j)
      for(int t = 0; t < len[j]; ++t)
      for(int k = 0; k < (1 << tc); ++k) {
        if(~dp[i][j][t][k]) printf("dp[%d][%d][%d][%d]=%d\n", i, j, g[j][t + 1], k, dp[i][j][t][k]);
      }*/
  int ans = 0, tot = (1 << tc) - 1;
  for(int i = 0; i < tc; ++i)
    for(int j = 0; j < tc; ++j) 
      for(int k = 0; k < 10; ++k) {
      if(~dp[i][j][k][tot]) Add(ans, dp[i][j][k][tot]);
    }
  printf("%d\n", ans);
  return 0;
}